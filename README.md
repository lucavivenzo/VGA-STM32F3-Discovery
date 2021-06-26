# Progetto P1 Sistemi Embedded
## Gruppo 13: Marra, Papulino, Staiano, Vivenzo
L’obiettivo di questo elaborato è la progettazione, ed il successivo sviluppo, di un’applicazione basata sulle librerie HAL e sulle librerie STemWin offerte all’interno del package STM32Cube. L’idea è quindi quella di interfacciare la scheda a nostra disposizione (STM32F3-Discovery / STM32F303VC) con uno schermo VGA utilizzando hardware esterno e mostrando a video delle immagini di output.
La documentazione è disponibile sulla [Wiki](http://www.naplespu.com/es/index.php?title=Sviluppo_di_un%27applicazione_basata_su_middleware_STM32Cube:_graphics,_display_(VGA/HDMI))
Un video della Demo realizzata è disponibile su [Youtube](https://www.youtube.com/watch?v=aGSfR4g1vQc)

# Come eseguire l'applicazione di Demo
Come prima cosa è necessario procurarsi STM32CubeF3 (nel Makefile, la radice è `STM_DIR`). Il contenuto della nostra repository dovrà essere apposto in una cartella creata all'interno di `$STM_DIR\Projects\STM32F3-Discovery`. Per poter compilare sulla propria macchina è necessario modificare opportunamente i campi `STM_DIR` e `DEM_DIR` all'interno del makefile nella radice della repository.

A questo punto per compilare sarà sufficiente eseguire all'interno della cartella p1Gruppo13 i seguenti comandi:
```
$ make prepare
$ make
```

