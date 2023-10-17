# **SWO3-Übungen - WS2023/24 - Übungszettel 2 - Ausarbeitung**

## **Beispiel 1**

# **a)**

So wie die Schnittstelle definiert ist, sieht es so als würde das Polynom "4 + 3*x - 2*x^2 + x^3" so p = {4, 3, -2, 1} im Array p abgespeichert sein. Wobei die Variable m die höchste Potenz angibt. Zum Ausgeben, würde ich eine eigene Funktion schreiben, die in einer For-Schleife über alle Elemente des Arrays iteriert und diese ausgibt. Dabei muss unterschieden werden zwischen + und - und dem Sonderfall x^0 (gar nicht anzeigen) und wenn ein Koeffizient 1 ist soll er auch nicht angezeigt werden.

# **b)**

Um den Wert des Polynoms an einer Stelle zu berechnen kann man einfach den Wert eines jeden Terms berechnen und dann die Summe bilden. Wobei man jeweils für x einsetzt und die Potenz berücksichtigt.

# **c)**

Um zwei Polynome zu addieren, muss man nur deren Koeffizienten paarweise addieren. Dies kann man mit einer For-Schleife machen. Um die Grenze der Schleife zu ermitteln, nimmt man einfach das größere der zwei Eingangsarrays.

# **d)**

Um zwei Polynome zu multiplizieren, muss jeder Koeffizient des einen Polynoms mit jeweils allen Koeffizienten des anderen Polynoms multipliziert werden. Diese Aufgabenstellung klingt nach zwei For-Schleifen. Die Grenzen der Schleifen sind jeweils die Potenz des Eingangarrays.

# **e)**

Teile und Herrsche

### **Lösungsidee**

### **Testfälle**
