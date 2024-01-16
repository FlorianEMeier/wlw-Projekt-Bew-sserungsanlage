
Abstract:
Dieses Projekt simuliert die Überwachung und Steuerung einer Bewässerungsanlage.


Funktionsweise:
Der Raspberry Pi ist der Server und die html Seite der Client. Der Server schickt alle 1 Sekunden die Werte eines Feuchtigkeitsensors an den Client der diese darstellt.
Der obere Graph stellt die Aktuellen Werte dar der letzten 20 Sekunden. Der untere Chart die Werte der letzten 24 Stunden. Man kann den mindest Feuchtigkeits Wert eingeben auf dem Client, der diese auch auf den Server zurückgibt. 
Wenn die Feuchtigkeit unter dem Wert ist sieht man es auf der Website ein Alarm, sowie ein LED leuchten.
Wenn man auf der Website den Knopf "Wasser geben" drückt, wird ein weiteres LED eingeschaltet, dieses simuliert die Pumpe. Die Pumpe läuft bis die Feuchtigkeit wieder den Mindestwert +10 erreicht hat.

Vorschau Client:
![MicrosoftTeams-image (1)](https://github.com/FlorianEMeier/wlw-Projekt-Bew-sserungsanlage/assets/131971911/2b0cf0ad-4b0f-4fc6-b62f-f8a113482770)



Code:
Der Server basiert auf Flask und der Client ist eine html Datei. Da der Flask server verlangt das die html in einer spezifischen Ordner struktur ist, sind diese nicht in Server und Client gesplitted.
Da der Feuchtigkeitsensor einen Analogen Wert ausgibt, wurde ein ESP verwendet der diesen ausliest und dann Bitweise an den Raspberry Pi schickt.
Dieser Wert wird heruntergebrochen in Werte von 0-100. 0 ist trocken und 100 komplett in Wasser. Dieser Wert wird zusammen mit der aktuellen Zeit dem Client übergeben.
Die Server Client Kommunikation läuft über Post Requests.
Die Html Webseite hat die Chart.js Library eingebunden zur Darstellung der Graphen.

Probleme:
Die Echtzeit Darstellung der Daten ist nicht vorhanden. Nach drücken des "Okay" Knopfes werden die Daten im Graph dargestellt. Die Funktionen der Buttons wurde Serverseitig auch noch nicht fertig gestellt.


Inbetriebnahme:
Starten des Codes auf dem ESP.Starten der Serverdatei mit Python auf dem Raspberry Pi. Der Client kann angeschaut werden mit der Addresse: http://192.168.239.68:5000.
