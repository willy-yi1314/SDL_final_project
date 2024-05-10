#pragma once
#include "ecs/system.h"

namespace fuse::ecs
{
    struct frame_animation_system:system
    {
       FUSE_INLINE void update(float){
        for(auto& e:view<animation_component>()){
            //get components
            auto& tr = e.get_component<transform_component>();
            auto& sp = e.get_component<sprite_component>();
            
            //get animation from asset registry
            auto& anim = _assets->get<animation_asset>(an.animation)->instance;

            //compute current frame
            int index = (get_ticks_ms()/anim.speed) % anim.frames.size();
            auto& frame = _assets->get<texture_asset>(anim.frames[index])->instance;

            //define target viewport
            SDL_FRect dst{
                tr.translate.x, tr.translate.y,
                sprite.width * tr.scale.x, sprite.height * tr.scale.y
            };

            //render sprite
            SDL_RenderCopyExF(_renderer, sprite.data, NULL, &dst, tr.rotation, NULL, sp.flip);

        }
       }
    };
    
} // namespace fuse::ecs
