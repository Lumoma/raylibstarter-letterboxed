#include "character.h"

void character::draw() {
    Rectangle source;
    source.width = 32;
    source.height = 32;
    source.x = isMoving ? (stateAge / keyframeDuration % keyframes) * 32 : 0; //Funktion Erklärung*
    source.y = 32 * orientation;
    Rectangle dest;
    dest.width = 32;
    dest.height = 32;
    dest.x = currentPos.x;
    dest.y = currentPos.y;
    DrawTexturePro(tex, source, dest, {}, 0, WHITE);
}

/*Funktion Erklärung*:
Die bedingte Zuweisung in diesem Code basiert auf dem ternären Operator "?":
1. Wenn isMoving wahr (true) ist (d.h. das Objekt bewegt sich) wird der Ausdruck
    (stateAge / keyframeDuration % keyframes) * 32 ausgeführt und der Wert wird source.x zugewiesen.
2. (stateAge / keyframeDuration % keyframes) berechnet den Zustand des aktuellen Schlüsselbildes,
    basierend auf dem aktuellen Zustandsalter und der Dauer eines Schlüsselbildes.
3. "* 32" multipliziert den berechneten Zustand mit 32, um die X-Koordinate des Quellbereichs (Player_Spritesheet) zu bestimmen.
4. Wenn isMoving falsch (false) ist (d.h., das Objekt bewegt sich nicht), wird der Wert 0 source.x zugewiesen (Blickrichtung vorne).*/

void character::drawPosStats() {
    DrawText(TextFormat("player: PosX: %.0f  PosY: %.0f", currentPos.x, currentPos.y - Y_OFFSET_STATUSBAR), 400, 24, 20, WHITE);
    DrawText(TextFormat("Tile PosX: %.0f  Tile PosY: %.0f", currentPos.x / 32 , (currentPos.y / 32) - (Y_OFFSET_STATUSBAR / 32)), 24, 24, 20, WHITE);
}