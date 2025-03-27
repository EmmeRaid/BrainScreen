# BrainScreen
# 🎮 Giroscopio per Rotazione Automatica dello Schermo con ESP32 e MPU6050  

Questo progetto utilizza un **ESP32** con un sensore **MPU6050** per rilevare l'inclinazione e ruotare automaticamente un display secondario su un PC tramite **Python**.  

---

## ⚙️ **Funzionamento**
1. L'ESP32 legge i dati dell'accelerometro dal **MPU6050**.
2. Calcola l'angolo di inclinazione rispetto alla posizione iniziale.
3. Invia il valore dell'angolo (0-360°) al PC via **porta seriale**.
4. Uno script Python interpreta i dati e ruota il **display secondario** usando la libreria **rotatescreen**.  

---

## 🔧 **Hardware Necessario**
✔ **ESP32** (o un microcontrollore compatibile)  
✔ **MPU6050** (modulo accelerometro/giroscopio)  
✔ **Cavi jumper** per collegare ESP32 e MPU6050  
✔ **PC con Windows** (o compatibile con rotatescreen)  

---

## 🔌 **Collegamenti Hardware**
| **MPU6050** | **ESP32** |
|------------|----------|
| VCC        | 3.3V     |
| GND        | GND      |
| SDA        | GPIO 23  |
| SCL        | GPIO 22  |

---

## 💾 **Software Necessario**
✅ **Arduino IDE** (per caricare il codice sull'ESP32)  
✅ **Python 3.x** (per lo script che ruota lo schermo)  
✅ **Librerie Python:**  
   ```bash
   pip install pyserial rotatescreen
