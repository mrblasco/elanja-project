Ho aggiunto un file con i comandi della SVN e uno script bash.

Per eseguire lo script:

./apritutto.sh

automaticamente apre tutti i file con il codice, le definizioni, tutte le cose utili.

Lo script e' pensato per usare l'editor gedit, se voi ne usate uno diverso, basta che sostituite la parola <gedit> con quello che preferite:

....... gedit ......  -------> ...... kate .......

Ho aggiunto anche uno script per aprire i file .tex; eseguire:

./latex.sh

automaticamente apre tutti i file .tex che stanno dentro la cartella doc.
Utilizza il programma Kile, che riconosce ed ha un sacco di cose utili per manipolare i file .tex, se non lo avete ancora istallato e lo volete, fate:

sudo apt-get install kile

se invece utilizzate un altro programma, dovete fare come sopra, all'interno dello script sostituire la parola kile con il nome del vostro programma preferito.

#---------------------------------------------------------------------------------------------------------#

Compilazione:

andate nella cartella principale del progetto ed eseguite:

1) make	model	compila tutto il progetto in modalita' testuale
2) make graphic	compila tutto il progetto in modalita' grafica
3) make test	compila solo test

Per eseguire il progetto dovete eseguire:

./elanja
./test

#---------------------------------------------------------------------------------------------------------#
Ho creato uno script R_script.sh che genera in automatico il grafico della simulazione eseguita.
Per invocarlo dovete fare: ./R_script.sh <numeroAgenti>
