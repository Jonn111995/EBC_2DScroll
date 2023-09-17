#include "RespawnManager.h"
#include "DxLib.h"
#include "../../System/ScreenInfo.h"
#include "../../System/SoundManager.h"
#include"../Source/GameObject/StageObject/Character/Character.h"

namespace {
    float INFORM_TIME = 1.f;
}

RespawnManager::RespawnManager()
    : now_state(ERespawnManagerState::kOBSERVE)
    , observe_object(nullptr)
    , inform_count_time(0.f)
    , is_pass_check_point(false)
{
}

RespawnManager::~RespawnManager()
{
}

void RespawnManager::Initialize() {
    __super::Initialize();
    SoundManager* sound_manager = SoundManager::GetInstance();
    inform_pass_check_point_sound = sound_manager->LoadSoundResource("Resources/Sounds/SE/se_pass_check_point.mp3");
}

void RespawnManager::Update(float delta_seconds) {
    __super::Update(delta_seconds);
    switch (game_object_state) {
    case EGameObjectState::kPLAYING:
        switch (now_state) {
        case ERespawnManagerState::kOBSERVE:
            if (observe_object != nullptr) {
                Vector2D object_pos = observe_object->GetPosition();

                //チェックポイント通過確認
                if (object_pos.x >= next_check_point.x) {
                   
                    is_pass_check_point = true;
                    now_check_point = next_check_point;
                    inform_movement = initial_velocity;
                    SoundManager::GetInstance()->PlayLoadSound(inform_pass_check_point_sound);
                    now_state = ERespawnManagerState::kINFORM_PASS_POINT;

                    //次のチェックポイント設定
                    for (int i = 0; i < check_point_list.size(); i++) {
                        if (now_check_point == check_point_list[i]) {

                            if (!(i + 1 >= check_point_list.size())) {
                                next_check_point = check_point_list[i + 1];
                            }
                            else {
                                next_check_point = check_point_list[i];
                                is_pass_last = true;
                            }

                        }
                    }
                }
            }
            break;
        case ERespawnManagerState::kINFORM_PASS_POINT:
            inform_count_time += delta_seconds;
            inform_movement -= plus;

            if (inform_count_time >= INFORM_TIME) {
                inform_count_time = 0.f;
                is_pass_check_point = false;
                now_state = ERespawnManagerState::kOBSERVE;

                if (is_pass_last) {
                    OffActive();
                    SetEnd();
                }
            }
            break;
        default:
            break;
        }
    case EGameObjectState::kPAUSE:
        break;
    case EGameObjectState::kEND:
        break;
    }
}

void RespawnManager::Draw(const Vector2D& screen_offset) {
    __super::Draw(screen_offset);
    switch (now_state) {
    case ERespawnManagerState::kINFORM_PASS_POINT:
        if (is_pass_check_point) {
            unsigned int color = GetColor(255, 0, 0);
            DrawFormatString(0, static_cast<float>(180+ inform_movement), color, "pass check point!!");
        }
        break;
    default:
        break;
    }
}

void RespawnManager::Finalize() {
    observe_object = nullptr;
    check_point_list.clear();
}

void RespawnManager::SetCheckPointList(std::vector<Vector2D> check_point_list) {
    this->check_point_list = check_point_list;
    now_check_point = check_point_list[0];
    next_check_point = check_point_list[1];
}

void RespawnManager::RespawnObject() {
    ScreenInfo* screen_info = ScreenInfo::GetInstance();

    int x_left = now_check_point.x - observe_object->GetBodyCollision().center_position.x;
    int y_top = now_check_point.y - observe_object->GetBodyCollision().center_position.y;
    observe_object->SetPosition(Vector2D(x_left, y_top));

    float center_pos_x = observe_object->GetPosition().x + observe_object->GetBodyCollision().center_position.x;
    float center_pos_y = observe_object->GetPosition().y + observe_object->GetBodyCollision().center_position.y;
    observe_object->SetCenterPosition(Vector2D(center_pos_x, center_pos_y));

    observe_object->SetHp(observe_object->GetMaxHp());
}