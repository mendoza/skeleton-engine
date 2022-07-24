function getRandom(m, n)
    local rand = math.random(m, n)
    return rand
end
actorTable = {
    graphicComponent = {
        spriteName = "bones",
        spriteFilepath = "assets/spritesheets/player.png",
        animated = true,
        animation = {
            switchTime = 1 / 10,
            rows = 4,
            cols = 3,
            initialImage = {
                row = 0,
                col = 0
            },
            animations = {{
                name = "idle",
                row = 0
            }, {
                name = "walking",
                row = 1
            }, {
                name = "punching",
                row = 2
            }, {
                name = "dying",
                row = 3
            }}
        },
        scale = {
            width = 3,
            height = 3
        },
        origin = {
            x = 30,
            y = 40
        },
        position = {
            x = 200,
            y = getRandom(1, 600)
        },
        spriteOrientation = {
            x = 1,
            y = 0
        }
    },

    physics = {
        speed = 100
    },

    update = function(dt)
        playAnimation("walking")
        count = 0
        for _ in pairs(tbl) do
            count = count + 1
        end
        message = "" .. tostring(getRandom(0, count))
        print(message)
        logger:Warning("" .. message)
        -- console:Warning(""..graphicComponent.animation.animations[])
    end

}
