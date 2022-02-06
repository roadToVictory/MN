set term png # ustawienie typu terminala, np. m.in. x11 (ekran), postscript, pdf, png, table (kolumny współrzędnych). 

set out "z1.png" # ustawienie nazwy pliku wyjściowego 

set xtics 0, 2.5, 20.0; 
set ytics -1, 0.25, 1; 
set xl "t" # tytuł osi x
set yl "x(t)" # tytuł osi y
set title "Wychylenie x(t)" # tytuł wykresu

plot "wyniki.txt" u 1:2 w p lt 3 pt 6 lw 3 t " x(t), h=0.1", cos(x) with lines lt 120 title "cos(t)"