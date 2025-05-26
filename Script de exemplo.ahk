#Requires AutoHotkey v2.0

CoordMode("Mouse", "Screen")  ; Garante que as coordenadas são absolutas da tela

; Clica em posições absolutas da tela quando F13–F16 são pressionadas

^F13:: {  ; X+ (Botão azul)
    MouseClick("left", 1452, 340)
}

^F14:: {  ; X- (Botão amarelo)
    MouseClick("left", 357, 794)
}

^F15:: {  ; Y+ (Botão vermelho)
    MouseClick("left", 305, 352)
}

^F16:: {  ; Y- (Botão verde)
    MouseClick("left", 1472, 823)
}
