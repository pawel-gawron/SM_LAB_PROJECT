# SM_LAB_PROJECT
 
W ramach projektu wykonano URA prędkości obrotowej wentylatora, sterowanego za pomocą sygnału PWM.

Skonstruowany URA ma za zadanie regulować prędkość obrotową wentylatora, sygnałem wymuszenia jest zadana wartość prędkości wyrażonej w obrotach na sekundę. Zakres regulacji <30, 100> obr/s. Projekt umożliwia dwojakie zadawanie prędkości - poprzez enkoder oraz za pomocą komunikacji poprzez port szeregowy. 

## Wymagania sprzętowe
Zestaw ewaluacyjny NUCLEO-F746ZG,

Enkoder,

Wyświetlacz LCD 2x16 + konwerter I2C LCM1602,

Wentylator do NVIDIA Jetson Nano 4020-PWM-5V,

Komparator napięcie LM393,

Rezystory Pull-up 2x1kΩ oraz rezystory do stworzenia dzielnika napięcia generującego napięcie referencyjne do komparatora - 2x1kΩ.

<img src="https://user-images.githubusercontent.com/65308689/156624290-92c33493-190e-4bff-aace-2287f2c9f7e8.jpg" width="700">

Prezentacja układu

## Dedykowana aplikacja desktopowa jako graficzny interfejs użytkowanika
<img width="700" alt="aplikacja_desktop" src="https://user-images.githubusercontent.com/65308689/156623894-0a109a9e-9ed0-40b6-8704-73a3975951b3.png">
Aplikacja desktopowa napisana w jęzuku Python przy użyciu biblioteki Tkinter.

## Dedykowane skrypty lub modele symulacyjne do logowania sygnałów sterujących i pomiarowych

<img src="https://user-images.githubusercontent.com/65308689/156624025-bfa8e120-8ddf-4824-a1d4-ed71ecc5336b.png" width="700">

Aplikacja ''System Identyfication'' pozwalająca na zbadanie układu

<img src="https://user-images.githubusercontent.com/65308689/156624048-d94b65d2-2fde-411c-acb1-d9193169047a.png" width="700">

Aplikacja ''PID Tuner'' pozwalająca na dobór nastaw regulatora

## Program

<img src="https://user-images.githubusercontent.com/65308689/156625780-23b80447-5d39-4402-8045-f18f560bceb2.png" width="700">

Schemat blokowy

Regulację obsłużyliśmy regulatorem PID który został zaimplementowany na podstawie równania równoległego regulatora PID. Jako wynik generuje on wartość wypełnienia sygnału PWM. Postanowiliśmy również przeciwdziałać zjawisku nacałkowywania się układu za pomocą anty-windup'a. Sygnał PID należało ograniczyć ze względu na sposób działania wypełnienia PWM. Zakres wynosi od 0 do 1000.

Pomiar prędkości obsłużyliśmy za pomocą timera w trybie Input Capture co pozwoliło nam na pomiar czasu pomiędzy każdym impulsem (dwa impulsy na obrót). Podczas pomiaru prędkości natrafiliśmy na problem jej pomiaru przy zerowej prędkośći. W takim przypadku pomiar wskazywał nam dodatnią wartość. Postanowiliśmy zapobiec temu poprzez zerowanie jej przy zerowej wartości zmiennej "output" która była obliczoną wartością regulatora PID.

Do obsługi wyświetlacza wykorzystaliśmy gotową bibliotekę w komunikacji I2C. W znaczącym stopniu ułatwiło to spełnienie założonych wymagań oraz pozwoliło na redukcję niepotrzebnego okablowania układu. Potrzebuje on wprowadzenia opóźnienia w pętli. Zdecydowaliśmy się na 20ms co odpowiada 50Hz. Jest to wartość z przedziału 50Hz-60Hz co wystarcza ludzkiemu oku. Oczywiście poprzez charakterystykę pętli while nie będzie to dokładnie taka wartość, lecz jest akceptowalne w naszym zastosowaniu.
