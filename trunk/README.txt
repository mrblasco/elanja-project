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

#---------------------------------------------------------------------------------------------------------#

Ho fatto un po di pulizia delle cose inutili e ho modificato il progetto cosi' che prenda in input il numero di agenti, il numero di iterazioni e la distanza del vicinato da considerare.
Ho inoltre modificato lo script che non si chiama piu' R_script.sh ma elanja.sh che serve per eseguire il progetto e visualizzare tutte le figure.
Per usarlo dovete fare:
	./elanja.sh <n agenti> <n iterazioni> <distanza> <opzione per le figure> <n sumulazioni>

Per ora, anche se fate piu' di una simulazione non vengono salvati i risultati, dato che si usa sempre i soliti file per i risultati.

#---------------------------------------------------------------------------------------------------------#
IMPORTANTE
Abbiamo ufficialmente deciso di scrivere il codice in c++, dato che le fltk si possono usare solo in c++. Dobbiamo creare un mega IF nel main in modo da poter scegliere se fare una esecuzione grafica o testuale del progetto; le funzioni che abbiamo fatto andranno modificate per essere inserite in classi c++.
Questo perchè altrimenti non possiamo modificare i parametri del modello mentre si fa la simulazione, ma una volta modificato un parametro dovremmo far rifare la simulazione testuale e poi leggere i file creati per farli vedere nell'interfaccia grafica.

