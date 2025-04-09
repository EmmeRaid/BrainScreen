import serial
import rotatescreen
import time

# Inizializza la comunicazione seriale
ser = serial.Serial('COM3', 9600)  # Sostituisci con la porta seriale corretta
time.sleep(2)  # Tempo per stabilire la connessione

# Ottieni i display secondari (se ce ne sono)
screens = rotatescreen.get_secondary_displays()

# Verifica se sono stati trovati display secondari
if len(screens) > 0:
    screen = screens[0]  # Usa il primo display secondario

    # Inizializza una variabile per mantenere traccia dell'orientamento precedente
    last_orientation = None
    last_angle = None  # Variabile per tracciare l'angolo precedente
    min_angle_change = 5  # Soglia minima di cambiamento dell'angolo per aggiornare l'orientamento

    # Ruota lo schermo in base ai dati ricevuti dal giroscopio
    while True:
        try:
            # Leggi i dati dalla porta seriale
            if ser.in_waiting > 0:
                angle_x = int(ser.readline().decode().strip())
                print(f"Angolo ricevuto dal giroscopio: {angle_x} gradi")

                # Ignora letture troppo piccole per evitare oscillazioni
                if last_angle is not None and abs(angle_x - last_angle) < min_angle_change:
                    continue  # Salta questa lettura se il cambiamento è inferiore alla soglia

                # Determina l'orientamento in base all'angolo
                if 0 <= angle_x < 80:
                    new_orientation = 0  # Orizzontale
                elif 80 <= angle_x < 190:
                    new_orientation = 90  # Verticale
                elif 190 <= angle_x < 280:
                    new_orientation = 180  # Orizzontale opposto
                elif 280 <= angle_x < 360:
                    new_orientation = 0 # Verticale opposto
                else:
                    new_orientation = last_orientation  # Mantieni l'orientamento precedente se l'angolo è fuori intervallo

                # Verifica se l'orientamento è cambiato
                if new_orientation != last_orientation:
                    print(f"Ruotando il display a {new_orientation} gradi...")
                    screen.rotate_to(new_orientation)
                    last_orientation = new_orientation  # Aggiorna l'orientamento precedente
                    time.sleep(1.5)  # Attendi un po' per stabilizzare il display

                # Memorizza l'angolo corrente per la prossima iterazione
                last_angle = angle_x

            time.sleep(0.1)  # Ritardo per evitare una lettura troppo rapida

        except ValueError:
            print("Errore nella lettura del dato seriale")
        except KeyboardInterrupt:
            print("Interruzione dell'esecuzione...")
            break
else:
    print("Nessun display secondario trovato.")
