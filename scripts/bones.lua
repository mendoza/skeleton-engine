contador = 1

function getRandom(m, n)
    local rand = math.random(m, n)
    return rand
end

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
}

physics = {
    speed = 100
}

function update(dt)
    local speed = physics["speed"] * dt
    forward(speed)
    playAnimation("walking")
    if (position.x < 0 or position.x > 400) then
        console:Log("Flipped at " .. position.x)
        flipH()
    end
    contador = contador + 1
end
