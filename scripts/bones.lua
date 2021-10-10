contador = 0

graphicComponent = {
    spriteName = "bones",
    spriteFilepath = "assets/spritesheets/player.png",
    animated = true,
    animation = {
        rows = 4,
        cols = 3,
        initialImage = {
            row = 0,
            col = 0
        },
        animations = {
            {
                name = "idle",
                row = 0
            },
            {
                name = "walking",
                row = 1
            },
            {
                name = "punching",
                row = 2
            },
            {
                name = "dying",
                row = 3
            }
        }
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
        y = 200
    },
    spriteOrientation = {
        x = 1,
        y = 0
    }
}

physics = {
    speed = 1
}

function update()
    if (contador%2 == 0) then
        playAnimation("dying")
        forward()
    else
        playAnimation("idle")
        stop()
    end
    contador = contador + 1
end