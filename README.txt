*************************IMPORTANTE********************************
Ora la parte grfica inizia a funzionare decentemente, manca ancora il disegno delle palline ma l'interfaccia funziona e ci sono tutte le cose che ci devono essere. Ho cambiato elggermente la disposizione delle scroll bar dato che erano veramente identiche a quelle precedenti dell' altro progetto.
Per eseguire il progetto grafico, andare dentro la cartella elanja-fltk e digitare il comando make, poi eseguire ./elaja per visualizzare l'interfaccia.
*******************************************************************

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

1) make	textual	compila tutto il progetto in modalita' testuale
2) cd elanja.fltk/ e poi make per compilare il progetto nella modalita' grafica

#---------------------------------------------------------------------------------------------------------#

Il progetto testuale accetta anche parametri da input lo potete eseguire o come ./elanja ed utilizza i parametri di default oppure li potete scrivere explicitamente.

#---------------------------------------------------------------------------------------------------------#

