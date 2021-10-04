contador = 0

graphicComponent = {
    spriteName = "bones",
    spriteFilepath = "assets/icon.png",
    scale = {
        width = 0.25,
        height = 0.25
    },
    origin = {
        x = 32,
        y = 32
    },
    position = {
        x = 200,
        y = 200
    },
    spriteOrientation = {
        x = 0,
        y = 1
    }
}

physics = {
    speed = 5
}

function update()
    if (contador % 10 == 0) then
        forward()
    elseif (contador % 5 == 0) then
        -- rotate(90)
    end
    contador=contador + 1;
end