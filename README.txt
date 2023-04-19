ICP 2022/2023 - PACMAN

AUTORI:
	Martin Kubička (xkubic45)
	Matěj Macek (xmacek27)

ZADANIE:
	Úlohou bolo implementovať hru celosvetovo známu hru PacMan s využitím objektovo 		orientovaného 	programovania v jazyku C++ a QT.

INTERAKTÍVNE PRVKY:
	Rozhodli sme sa implementovať následujúce iteraktívne prvky:
		- Životy
		- Skóre

OVLÁDANIE:
	HRA:
		W - Pohyb hore
		A - Pohyb doľava
		S - Pohyb dole
		D - Pohyb doprava
	PREHRÁVANIE:
		R - Súvislé prehrávanie dopredu
		E - Zastavenie súvislého prehrávania
		B - Súvislé prehrávanie dozadu
		P - Krok späť
		N - Krok ďalej
		
		Prepínanie módov:
			Keď chcem prepnúť mód z súvislého prehávania na jednotlivé kroky, tak 			musíme stlačiť klávesu E.
	
LOGOVANIE:
	Logovanie priebehu poslednej hry je uložené v log/log.txt.
	Vždy je na začiatku logu vypísaná mapa a ďalej sú následujúce skratky:
		MAP map_name - Mapa poslednej hry
		GS - Štart hry
		PCM X Y - Posunutie PacMan na pozíciu X Y
		GM ID X Y - Posunutie Ducha s ID na pozíciu X Y
		KEY ID - Získanie kľúču s ID
		KILL - Stretnutie PacMana a Ducha
		GE - Koniec hry

ARCHÍV EXAMPLES:
	V archíve examples je príklad mapy, ktorá môže byť zahraná a k nej aj log, ktorý môže 	byť prehraný.

PREKLAD:
	make

VERZIA QT:
	5.9.7