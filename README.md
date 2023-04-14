# TODO
### pacman
- naprogramovat aby kdyz se zmackla mys tak aby pacman dojel na pozici kde se kliklo
    -A* / nejaky podobny algoritmus -> bude to v pacman handler pak volani pacman move 

### ghost
- doresit pohyb pacmana -> slo by zvolit taky A* 

### bugs
- celkovo UI pomenit - MARTIN

### Ostatne
- ked spustim zo /src tak sa nenajdu grafiky - MARTIN
- velkost pisma na mainpage je zly na inych platformach - MARTIN

- spustit ako ./pacman -> spravit spravny makefile (make, make clean, make run, make pack, make doxygen)
- warningy fixnut??
- komentare
- dokumentacia -> doxygen (make doxygen)
- skusit ci funguje na linuxe aj na windowse
- README.txt

---------------------------------------------------------------------------------------------------------------------------------------------------------------
# PacMan

## Všeobecné informácie
Súbor main.cpp - main funkcia, ktorá bola automaticky vygenerovaná (nepotrebuješ riešiť)

Súbory mainwindow.cpp/.h - homepage (nepotrebuješ riešiť)

customgraphicsview.h - vlastná trieda QGraphicsView (nepotrebuješ riešiť)

map|field|end|ghost|key|pacman|path|wall .cpp/.h - rozhranie mapy
## Map logic
Mapa je vytvorená v súbore map.cpp/.h a obsahuje wall, end, key, pacman, path, ghost triedy ktoré sú všetky podtriedou Field.

Trieda Field ma atributy type (kukni enum vo field.h), x1, y2 (od px) x2,y2 (do px). Takže všetky triedy ako end, key atd.. dedia tieto atributy.

Mapa má atribut sizeOfBlock, čo predstavuje šírku a výšku jedného bloku (wall, path, end atd..).
Ďalej má atribut numberOfKeysLeft, ktoré sa increasuje tým, že je kľuč vytvorený. Treba potom spraviť, že keď je kluc zobratý, tak sa decreasuje a ked pacman bude na policku end tak musi byt tento atribut rovný 0. 

Mapa je vytvorená na scéne QGraphicsScene *scene, ktorú asi budeš musieť použiť keď budes chciet nieco pridat na mapu alebo odobrať atd..

Tvoj kod pridaj do Map constructoru v map.cpp (vyhladaj TODO a uvidis kam).

Dolezita funkcia ktora ti može pomoct je metoda triedy Map - getField, ktorej ked zadas x, y (px) suradnice ti vrati poličko (Field) na tých suraniciach (napríklad ti vrati Field Wall). Mozes to vyuzit pri tom, ked budes chciet vediet ci sa pacman moze pohnut napriklad hore. 

Príklad pouzitia:
```
 auto w = this->getField<Field *>(10, 10);
 if (w != nullptr) {
    if (w->type == WALL) {
        // viem ze tam je stena
    } elif (w->type == PATH) {
        // chodnik
    }

    // atd..
 }

```

Všetko je okomentovane, takze snad sa bude v tom dat nejako vyznať.

Preklad: make
QtVerzia: 5.9.7 (rovnaka ako na merlinovi)
