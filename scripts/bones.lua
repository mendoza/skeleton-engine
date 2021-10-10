contador = 0

graphicComponent = {
    spriteName = "bones",
    spriteFilepath = "assets/spritesheets/player.png",
    animated = true,
    animation = {
        rows = 4,
        cols = 3,
        initialImage = {
            row = 1,
            col = 0
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
    speed = 5
}

function update()
    forward()
end