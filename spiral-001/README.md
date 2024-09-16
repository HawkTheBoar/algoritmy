#LOOP
- Vykreslí se první čára
- Dokud je délka čáry větší než délka mezery
- Vykreslí se dvě čáry a vždy se pootočí o 90 stupňů do prava.
- Od délky se odečte délka mezery 
#REKURZE
- Vykreslí se první čára
- Zavolá se metoda step do které se předá délka
- Metoda vykreslí dvě čáry a vždy se pootočí o 90 stupňů do prava
- Volá sama sebe a předává vždy rozdíl délky a mezery dokud délka spirály je větší než délka mezery
