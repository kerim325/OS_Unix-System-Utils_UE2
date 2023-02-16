# OS_UE-2
Im Rahmen der Lehrveranstaltung OS (UE) der Universität Wien sollen die Programme uname, ps, pstree, killall and statx implementiert werden. 

## uname
In dieser Aufgabe soll der Syscall uname verwendet werden (man 2 uname), der Versions-Informationen über den aktuell laufenden Kernel abfragen kann. 
Nach dem Abfragen der Informationen, sollen folgende Informationen ausgegeben werden: <br>
 • OS: Name des Betriebssystems<br>
 • Hostname: Aktueller Hostname der Maschine<br>
 • Release: Release-Nummer des Kernels<br>
 • Version: Version des Kernels (e.g. preemptive/non-preemptive, etc.)

## ps
Es soll eine simple Variante des ps Linux-Tools nachgebaut werden. Folgende Informationen sollen gesammelt und im JSON Format (siehe Beispiel) ausgegeben
werden:<br>
• pid: Die PID des Prozesses<br>
• exe: Der Pfad zum Executable File des Prozesses<br>
• cwd: Das aktuelle Arbeitsverzeichnis des Prozesses<br>
• base_address: Die Basisadresse des Executable Files im Speicher (Dezimal)<br>
• state: Der aktuelle Prozessstatus<br>
• cmdline: Die vollständige Aufrufzeile des Prozesses, als Array

## pstree
In dieser Aufgabe sollen alle Prozesse und ihre Child-Prozesse hierarchisch aufgelistet werden, wieder mittels JSON output. Jede Node im Baum sollte folgende Informationen beinhalten:<br>
• pid: Die PID des Prozesses<br>
• name: Der Name des Prozesses<br>
• children: Array mit den Kindern des Prozesses

## killall
In dieser Aufgabe geht es darum, eine einfache Version des killall Programms nachzubauen. 
Es wird ein String als erster Commandline-Parameter übergeben (argv[1]). Alle Prozesse, die diesen String im Namen
enthalten, sollen mittels dem kill Syscall (man 2 kill) und dem SIGKILL Signal terminiert werden.

## statx
In dieser Aufgabe soll ein relativ neuer Syscall namens statx (man 2 statx) verwendet werden
(hinzugefügt in Linux 4.11). Dieser Syscall erlaubt das Bestimmen von Datei-Attributen, wie
Berechtigungen, Größe, etc. Es wird ein absoluter Pfad als erster Commandline-
Parameter übergeben (argv[1]). Zu abfragende Attribute sind: <br>
1. Berechtigungen: Beim ersten statx Aufruf sollen nur die Berechtigungen abgefragt werden,
und dabei einfach nur Read, Write, Execute für Owner, Group und Other. Diese Berechtigungen
sollen dann wie bei ls ausgegeben werden, z.B. rwxr-xr-x. <br>
2. UID/GID: Beim zweiten statx Aufruf sollen gleichzeitig die UID des Owners und die GID
der Gruppe der Datei abgefragt werden. Die IDs sollen dann so ausgegeben werden: UID:
1000, GID: 1000<br>
3. Dateigröße: Beim letzten statxAufruf soll die Dateigröße in Bytes abgefragt und in Dezimal
ausgegeben werden, z.B. 39503.<br>
