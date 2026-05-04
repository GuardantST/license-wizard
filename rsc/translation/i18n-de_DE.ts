<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.1" language="de_DE">
<context>
    <name>ActivationPageWidget</name>
    <message>
        <location filename="../../src/ActivationPageWidget.ui" line="68"/>
        <source>Back</source>
        <translation>Zurück</translation>
    </message>
    <message>
        <location filename="../../src/ActivationPageWidget.ui" line="81"/>
        <source>License activation</source>
        <translation>Aktivierung der Lizenz</translation>
    </message>
    <message>
        <location filename="../../src/ActivationPageWidget.ui" line="94"/>
        <source>For serial number activation a computer with access to the Internet is needed</source>
        <translation>Um die Seriennummer zu aktivieren, benötigen Sie einen Computer mit Internetzugang</translation>
    </message>
    <message>
        <location filename="../../src/ActivationPageWidget.ui" line="214"/>
        <source>On which computer do you want to use the license?</source>
        <translation>Auf welchem Computer möchten Sie die Lizenz verwenden?</translation>
    </message>
    <message>
        <location filename="../../src/ActivationPageWidget.ui" line="234"/>
        <source>On this</source>
        <translation>Auf dem laufenden</translation>
    </message>
    <message>
        <location filename="../../src/ActivationPageWidget.ui" line="259"/>
        <source>On another</source>
        <translation>Auf einem anderen</translation>
    </message>
    <message>
        <location filename="../../src/ActivationPageWidget.ui" line="284"/>
        <source>Write a license to a USB key to use it on any computer</source>
        <translation>Schreiben Sie die Lizenz auf einen USB-Stick, um sie auf einem beliebigen Computer zu verwenden</translation>
    </message>
</context>
<context>
    <name>CommandLineManager</name>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="113"/>
        <source>Usage:
license_wizard
    start in graphical mode
license_wizard --help
    show this help message
license_wizard --console &lt;operation&gt; &lt;arguments&gt;
    start in console mode, applying the specified operation with the
        specified arguments

Operations and their arguments:
--list
    show the licenses list
--activate &lt;serial_number&gt; --host &lt;url&gt;
    activate with a serial number
--update &lt;license_ID&gt; --host &lt;url&gt;
    update the specified license
--activate-request &lt;request_file_path&gt;
    create an activation request
--update-request &lt;license_ID&gt; &lt;request_file_path&gt;
    create an update request for the specified license
--activate-response &lt;serial_number&gt; &lt;request_file_path&gt; &lt;license_file_path&gt;
        --host &lt;url&gt;
    send the activation request
--update-response &lt;request_file_path&gt; &lt;license_file_path&gt; --host &lt;url&gt;
    send the update request
--activate-offline &lt;license_file_path&gt;
    activate with the license file
--update-offline &lt;license_file_path&gt;
    update with the license file
--rehost-extract &lt;license_ID&gt; &lt;rehost_file_path&gt;
    extract the license for rehost
--rehost &lt;rehost_file_path&gt; --host &lt;url&gt;
    rehost the specified license
--rehost-request &lt;fingerprint_file_path&gt;
    create a rehost request
--rehost-response &lt;rehost_file_path&gt; &lt;fingerprint_file_path&gt;
        &lt;license_file_path&gt; --host &lt;url&gt;
    send the rehost request
--rehost-offline &lt;license_file_path&gt;
    rehost with the license file
--dongle-set-license &lt;dongle_ID&gt; &lt;serial_number&gt; --host &lt;url&gt;
    activate on the specifed key with a serial number
--dongle-blink &lt;dongle_ID&gt;
    activate the specifed key LED blinking
</source>
        <translation>Anwendung:
license_wizard
    im Grafikmodus ausführen
license_wizard --help
    diese Hilfemeldung anzeigen
license_wizard --console &lt;Operation&gt; &lt;Argumente&gt;
    im Konsolenmodus ausführen, die angegebene Operation mit den angegebenen
        Argumenten anwenden

Operationen und deren Argumente:
--list
    Liste der Lizenzen anzeigen
--activate &lt;Seriennummer&gt; --host &lt;url&gt;
    mit einer Seriennummer aktivieren
--update &lt;Lizenz_ID&gt; --host &lt;url&gt;
    die angegebene Lizenz erneuern
--activate-request &lt;Anfrage_Datei_Pfad&gt;
    eine Aktivierungsanfrage erstellen
--update-request &lt;Lizenz_ID&gt; &lt;Anfrage_Datei_Pfad&gt;
    eine Anfrage für die Erneuerung der angegebenen Lizenz erstellen
--activate-response &lt;Seriennummer&gt; &lt;Anfrage_Datei_Pfad&gt;
        &lt;Lizenz_Datei_Pfad&gt; --host &lt;url&gt;
    eine Aktivierungsanfrage senden
--update-response &lt;Anfrage_Datei_Pfad&gt; &lt;Lizenz_Datei_Pfad&gt; --host &lt;url&gt;
    eine Erneuerungsanfrage senden
--activate-offline &lt;Lizenz_Datei_Pfad&gt;
    mit der Lizenzdatei aktivieren
--update-offline &lt;Lizenz_Datei_Pfad&gt;
    mit der Lizenzdatei erneuern
--rehost-extract &lt;Lizenz_ID&gt; &lt;Übertragung_Datei_Pfad&gt;
    Lizenz zur Übertragung zu extrahieren
--rehost &lt;Übertragung_Datei_Pfad&gt; --host &lt;url&gt;
    die angegebene Lizenz übertragen
--rehost-request &lt;Abdruck_Datei_Pfad&gt;
    eine Übertragungsanfrage erstellen
--rehost-response &lt;Übertragung_Datei_Pfad&gt; &lt;Abdruck_Datei_Pfad&gt;
        &lt;Lizenz_Datei_Pfad&gt; --host &lt;url&gt;
    eine Übertragungsanfrage senden
--rehost-offline &lt;Lizenz_Datei_Pfad&gt;
    mit der Lizenzdatei übertragen
--dongle-set-license &lt;dongle_ID&gt; &lt;serial_number&gt; --host &lt;url&gt;
    mit einem bestimmten Schlüssel und einer Seriennummer aktivieren
--dongle-blink &lt;dongle_ID&gt;
    Blinken der LED auf dem angegebenen Schlüssel aktivieren
</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="168"/>
        <source>License activation</source>
        <translation>Aktivierung der Lizenz</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="171"/>
        <source>License update</source>
        <translation>Erneuerung der Lizenz</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="173"/>
        <source>License activation request creation</source>
        <translation>Erstellen einer Anfrage für eine Lizenzaktivierung</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="175"/>
        <source>License update request creation</source>
        <translation>Erstellen einer Anfrage für eine Lizenzerneuerung</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="177"/>
        <source>License activation request sending</source>
        <translation>Senden einer Anfrage für eine Lizenzaktivierung</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="179"/>
        <source>License update request sending</source>
        <translation>Senden einer Anfrage für eine Lizenzerneuerung</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="181"/>
        <source>License rehost request creation</source>
        <translation>Erstellen einer Anfrage für eine Lizenzübertragung</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="183"/>
        <source>License extraction</source>
        <translation>Extraktion der Lizenz</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="186"/>
        <source>License rehost</source>
        <translation>Lizenzübertragung</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="188"/>
        <source>License rehost request sending</source>
        <translation>Senden einer Anfrage für eine Lizenzübertragung</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="190"/>
        <source>Setting license to the key</source>
        <translation>Aktivierung der Lizenz auf dem Schlüssel</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="195"/>
        <source>Unexpected operation</source>
        <translation>Unerwartete Operation</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="301"/>
        <source>Incorrect license ID format
Expected 0xNNNNNNNN, where each N is a hexadecimal digit</source>
        <translation>Falsches Format der Lizenz-ID
Erwartet 0xNNNNNNNN, wobei jedes Zeichen N eine hexadezimale Ziffer ist</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="306"/>
        <source>Incorrect dongle ID format
Expected 0xNNNNNNNN, where each N is a hexadecimal digit</source>
        <translation>Falsches Format der Schlüssel-ID
Erwartet 0xNNNNNNNN, wobei jedes Zeichen N eine hexadezimale Ziffer ist</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="311"/>
        <source>Incorrect serial number format
Expected NNNNNN-NNNNNN-NNNNNN-NNNNNN-NNNNNN, where each N is a Latin letter in upper or lower case or a digit</source>
        <translation>Falsches Format der Seriennummer
erwartet NNNNNN-NNNNNN-NNNNNN-NNNNNN-NNNNNN, wobei jedes Zeichen N ein Groß- oder Kleinbuchstabe des lateinischen Alphabets oder eine Ziffer ist</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="316"/>
        <source>File not found: %1</source>
        <translation>Datei nicht gefunden: %1</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="319"/>
        <source>Incorrect host URL format</source>
        <translation>Falsches Format der Serveradresse</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="322"/>
        <source>Incorrect file path</source>
        <translation>Falscher Dateipfad</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="328"/>
        <location filename="../../src/CommandLineManager.cpp" line="337"/>
        <location filename="../../src/CommandLineManager.cpp" line="430"/>
        <source>Internal error</source>
        <translation>Interner Fehler</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="346"/>
        <source>%1 completed</source>
        <translation>%1 abgeschlossen</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="408"/>
        <source>Option %1 must go first</source>
        <translation>Die Option %1 muss zuerst folgen</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="412"/>
        <source>Option %1 must go last</source>
        <translation>Die Option %1 muss auf die letzte Option folgen</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="416"/>
        <source>Incorrect number of arguments</source>
        <translation>Falsche Anzahl von Argumenten</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="419"/>
        <source>Option %1 has incorrect value</source>
        <translation>Die Option %1 hat einen ungültigen Wert</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="423"/>
        <source>Parameter has incorrect value</source>
        <translation>Parameter hat einen ungültigen Wert</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="426"/>
        <source>Unrecognized operation</source>
        <translation>Nicht erkannte Operation</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="456"/>
        <source>No licenses installed!</source>
        <translation>Es sind keine Lizenzen vorhanden!</translation>
    </message>
</context>
<context>
    <name>DonglePageWidget</name>
    <message>
        <location filename="../../src/DonglePageWidget.ui" line="124"/>
        <source>Code for the license writing</source>
        <translation>Code für die Erfassung einer Lizenz</translation>
    </message>
    <message>
        <location filename="../../src/DonglePageWidget.ui" line="143"/>
        <source>File with codes</source>
        <translation>Code-Datei</translation>
    </message>
    <message>
        <location filename="../../src/DonglePageWidget.ui" line="267"/>
        <source>Continue</source>
        <translation>Fortfahren</translation>
    </message>
</context>
<context>
    <name>FilePickingWidget</name>
    <message>
        <location filename="../../src/FilePickingWidget.ui" line="44"/>
        <source>Select a file, which you received as a result of an activation, an update or a rehost from another computer.</source>
        <translation>Wählen Sie die Datei aus, die Sie bei der Aktivierung, Erneuerung oder Übertragung einer Lizenz von einem anderen Computer erhalten haben.</translation>
    </message>
    <message>
        <location filename="../../src/FilePickingWidget.ui" line="60"/>
        <source>Select a fingerprint file, which you recevied from the computer, where you want to rehost the license to.</source>
        <translation>Wählen Sie die Abdruckdatei aus, die Sie von dem Computer erhalten haben, auf den Sie die Lizenz übertragen möchten.</translation>
    </message>
    <message>
        <location filename="../../src/FilePickingWidget.ui" line="70"/>
        <source>Select a file with codes for writing a license to the key.</source>
        <translation>Wählen Sie die Codedatei zur Erfassung der Lizenzen aus.</translation>
    </message>
    <message>
        <location filename="../../src/FilePickingWidget.ui" line="89"/>
        <source>Select a file</source>
        <translation>Eine Datei auswählen</translation>
    </message>
    <message>
        <location filename="../../src/FilePickingWidget.ui" line="202"/>
        <source>Incorrect file</source>
        <translation>Falsche Datei</translation>
    </message>
    <message>
        <location filename="../../src/FilePickingWidget.ui" line="222"/>
        <source>Select another one</source>
        <translation>Eine andere wählen</translation>
    </message>
    <message>
        <location filename="../../src/FilePickingWidget.cpp" line="233"/>
        <source>There are %1 codes (keys) in this file</source>
        <translation>Die Datei enthält %1 Codes (Schlüssel)</translation>
    </message>
</context>
<context>
    <name>LicenseItemWidget</name>
    <message>
        <location filename="../../src/LicenseItemWidget.ui" line="82"/>
        <source>Trial Software Key</source>
        <translation>Testversionsschlüssel</translation>
    </message>
    <message>
        <location filename="../../src/LicenseItemWidget.ui" line="110"/>
        <source>Vendor code</source>
        <translation>Zugangscode</translation>
    </message>
    <message>
        <location filename="../../src/LicenseItemWidget.ui" line="197"/>
        <source>Update license</source>
        <translation>Aktualisierung installieren</translation>
    </message>
    <message>
        <location filename="../../src/LicenseItemWidget.ui" line="239"/>
        <source>Check updates</source>
        <translation>Auf Aktualisierungen prüfen</translation>
    </message>
    <message>
        <location filename="../../src/LicenseItemWidget.ui" line="244"/>
        <source>Offline update</source>
        <translation>Offline-Aktualisierung</translation>
    </message>
    <message>
        <location filename="../../src/LicenseItemWidget.ui" line="249"/>
        <source>Move to another computer</source>
        <translation>Auf einen anderen Computer übertragen</translation>
    </message>
    <message>
        <location filename="../../src/LicenseItemWidget.ui" line="254"/>
        <source>Remove</source>
        <translation>Löschen</translation>
    </message>
    <message>
        <location filename="../../src/LicenseItemWidget.ui" line="259"/>
        <source>Write a license to this key</source>
        <translation>Die Lizenz auf diesen Schlüssel schreiben</translation>
    </message>
</context>
<context>
    <name>LicensePickingWidget</name>
    <message>
        <location filename="../../src/LicensePickingWidget.ui" line="44"/>
        <source>Select the license</source>
        <translation>Wählen Sie eine Lizenz</translation>
    </message>
    <message>
        <location filename="../../src/LicensePickingWidget.ui" line="176"/>
        <source>No licenses installed</source>
        <translation>Es sind keine Lizenzen vorhanden</translation>
    </message>
    <message>
        <location filename="../../src/LicensePickingWidget.cpp" line="309"/>
        <source>Select</source>
        <translation>Auswählen</translation>
    </message>
</context>
<context>
    <name>ListPageWidget</name>
    <message>
        <location filename="../../src/ListPageWidget.ui" line="71"/>
        <source>Licenses</source>
        <translation>Lizenzen</translation>
    </message>
    <message>
        <location filename="../../src/ListPageWidget.ui" line="91"/>
        <source>License activation</source>
        <translation>Aktivierung der Lizenz</translation>
    </message>
    <message>
        <location filename="../../src/ListPageWidget.ui" line="135"/>
        <source>No license found on this computer</source>
        <translation>Auf diesem Computer wurde keine Lizenz erkannt</translation>
    </message>
    <message>
        <location filename="../../src/ListPageWidget.ui" line="178"/>
        <source>What do you have?</source>
        <translation>Was haben Sie da?</translation>
    </message>
    <message>
        <location filename="../../src/ListPageWidget.ui" line="207"/>
        <source>Serial number, license file</source>
        <translation>Seriennummer, Lizenzdatei</translation>
    </message>
    <message>
        <location filename="../../src/ListPageWidget.ui" line="220"/>
        <source>Activate a license</source>
        <translation>Aktivieren Sie die Lizenz</translation>
    </message>
    <message>
        <location filename="../../src/ListPageWidget.ui" line="233"/>
        <source>USB key</source>
        <translation>USB-Stick</translation>
    </message>
    <message>
        <location filename="../../src/ListPageWidget.ui" line="246"/>
        <source>Insert it in this computer</source>
        <translation>Stecken Sie es in diesen Computer</translation>
    </message>
    <message>
        <location filename="../../src/ListPageWidget.ui" line="292"/>
        <source>Licensing
terms</source>
        <translation>Beschränkung der 
Lizenz</translation>
    </message>
    <message>
        <location filename="../../src/ListPageWidget.ui" line="298"/>
        <source>Concurrent
instances</source>
        <translation>Netzwerk-
Ressource</translation>
    </message>
    <message>
        <location filename="../../src/ListPageWidget.ui" line="304"/>
        <source>VM
enabled</source>
        <translation>Arbeiten 
an der VM</translation>
    </message>
    <message>
        <location filename="../../src/ListPageWidget.cpp" line="587"/>
        <source>The number of machines on which the Feature is running simultaneously</source>
        <translation>Anzahl der Rechner, auf denen die Komponente gleichzeitig läuft</translation>
    </message>
    <message>
        <location filename="../../src/ListPageWidget.cpp" line="590"/>
        <source>The number of API connections</source>
        <translation>Anzahl der API-Verbindungen</translation>
    </message>
    <message>
        <location filename="../../src/ListPageWidget.cpp" line="592"/>
        <source>The number of running instances of the Feature</source>
        <translation>Anzahl der ausgeführten Instanzen der Komponente</translation>
    </message>
</context>
<context>
    <name>MainPageWidget</name>
    <message>
        <location filename="../../src/MainPageWidget.ui" line="83"/>
        <source>Settings</source>
        <translation>Einstellungen</translation>
    </message>
    <message>
        <location filename="../../src/MainPageWidget.cpp" line="286"/>
        <location filename="../../src/MainPageWidget.cpp" line="310"/>
        <source>Internal error</source>
        <translation>Interner Fehler</translation>
    </message>
    <message>
        <location filename="../../src/MainPageWidget.cpp" line="288"/>
        <source>License installed</source>
        <translation>Lizenz eingerichtet</translation>
    </message>
    <message>
        <location filename="../../src/MainPageWidget.cpp" line="290"/>
        <source>License updated</source>
        <translation>Lizenz erneut</translation>
    </message>
    <message>
        <location filename="../../src/MainPageWidget.cpp" line="292"/>
        <source>License update available</source>
        <translation>Aktualisierung für die Lizenz verfügbar</translation>
    </message>
    <message>
        <location filename="../../src/MainPageWidget.cpp" line="294"/>
        <source>Licenses updates available</source>
        <translation>Lizenzaktualisierungen verfügbar</translation>
    </message>
    <message>
        <location filename="../../src/MainPageWidget.cpp" line="296"/>
        <source>No more license updates</source>
        <translation>Keine Aktualisierungen für Lizenzen verfügbar</translation>
    </message>
    <message>
        <location filename="../../src/MainPageWidget.cpp" line="298"/>
        <source>Unable to check license updates</source>
        <translation>Prüfung auf Aktualisierungen fehlgeschlagen</translation>
    </message>
    <message>
        <location filename="../../src/MainPageWidget.cpp" line="300"/>
        <source>Unable to check licenses updates</source>
        <translation>Prüfung auf Aktualisierungen fehlgeschlagen</translation>
    </message>
    <message>
        <location filename="../../src/MainPageWidget.cpp" line="302"/>
        <source>Unable to update the license</source>
        <translation>Aktualisierung der Lizenz fehlgeschlagen</translation>
    </message>
    <message>
        <location filename="../../src/MainPageWidget.cpp" line="304"/>
        <source>License extracted</source>
        <translation>Lizenz extrahiert</translation>
    </message>
    <message>
        <location filename="../../src/MainPageWidget.cpp" line="314"/>
        <source>License ID copied to clipboard</source>
        <translation>Lizenz-ID in die Zwischenablage kopiert</translation>
    </message>
</context>
<context>
    <name>MainWindow</name>
    <message>
        <location filename="../../src/MainWindow.cpp" line="345"/>
        <source>Entered data is not URL</source>
        <translation>Bei den eingegebenen Daten handelt es sich nicht um eine URL</translation>
    </message>
</context>
<context>
    <name>OfflinePageWidget</name>
    <message>
        <location filename="../../src/OfflinePageWidget.ui" line="84"/>
        <source>Offline activation</source>
        <translation>Offline-Aktivierung</translation>
    </message>
    <message>
        <location filename="../../src/OfflinePageWidget.ui" line="177"/>
        <source>New license</source>
        <translation>Neue Lizenz</translation>
    </message>
    <message>
        <location filename="../../src/OfflinePageWidget.ui" line="196"/>
        <source>License update</source>
        <translation>Erneuerung der Lizenz</translation>
    </message>
    <message>
        <location filename="../../src/OfflinePageWidget.ui" line="215"/>
        <source>License rehost</source>
        <translation>Lizenzübertragung</translation>
    </message>
    <message>
        <location filename="../../src/OfflinePageWidget.ui" line="274"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Save the &lt;span style=&quot; font-weight:600;&quot;&gt;fingerprint file&lt;/span&gt;. It contains info for license rehost with the help of another computer with access to the Internet.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Speichern Sie &lt;span style=&quot; font-weight:600;&quot;&gt;die Abdruckdatei&lt;/span&gt;. Sie enthält Informationen zur Lizenzübertragung über einen anderen Computer mit Internetzugang.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="../../src/OfflinePageWidget.ui" line="284"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Save the &lt;span style=&quot; font-weight:600;&quot;&gt;request file&lt;/span&gt;. It contains info for license activation on another computer with access to the Internet.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Speichern Sie &lt;span style=&quot; font-weight:600;&quot;&gt;die Anfragedatei&lt;/span&gt;. Sie enthält Informationen zur Aktivierung der Lizenz auf einem anderen Computer mit Internetzugang.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="../../src/OfflinePageWidget.ui" line="381"/>
        <source>Save</source>
        <translation>Speichern</translation>
    </message>
    <message>
        <location filename="../../src/OfflinePageWidget.ui" line="412"/>
        <source>Continue</source>
        <translation>Fortfahren</translation>
    </message>
    <message>
        <location filename="../../src/OfflinePageWidget.ui" line="473"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;1. Move the saved &lt;span style=&quot; font-weight:600;&quot;&gt;request file&lt;/span&gt; and &lt;span style=&quot; font-weight:600;&quot;&gt;serial number&lt;/span&gt; to the computer with access to the Internet.&lt;/p&gt;&lt;p&gt;2. Run the &lt;span style=&quot; font-weight:600;&quot;&gt;Guardant License Wizard&lt;/span&gt; application on it.&lt;/p&gt;&lt;p&gt;3. Push the «&lt;span style=&quot; font-weight:600;&quot;&gt;License activation&lt;/span&gt;» button and activate a license for another computer.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;1. Übertragen Sie die gespeicherte &lt;span style=&quot; font-weight:600;&quot;&gt;Anfragedatei&lt;/span&gt; und &lt;span style=&quot; font-weight:600;&quot;&gt;Seriennummer&lt;/span&gt; auf einen Computer mit Internetzugang.&lt;/p&gt;&lt;p&gt;2. Führen Sie die Anwendung &lt;span style=&quot; font-weight:600;&quot;&gt;Guardant Lizenz-Assistent&lt;/span&gt; darauf aus.&lt;/p&gt;&lt;p&gt;3. Klicken Sie auf «&lt;span style=&quot; font-weight:600;&quot;&gt;Lizenzaktivierung&lt;/span&gt;» und aktivieren Sie die Lizenz für den anderen Computer.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="../../src/OfflinePageWidget.ui" line="483"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;1. Move the saved &lt;span style=&quot; font-weight:600;&quot;&gt;request file&lt;/span&gt; to the computer with access to the Internet.&lt;/p&gt;&lt;p&gt;2. Run the &lt;span style=&quot; font-weight:600;&quot;&gt;Guardant License Wizard&lt;/span&gt; application on it.&lt;/p&gt;&lt;p&gt;3. Push the «&lt;span style=&quot; font-weight:600;&quot;&gt;License activation&lt;/span&gt;» button and update a license for another computer.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;1. Übertragen Sie die gespeicherte &lt;span style=&quot; font-weight:600;&quot;&gt;Anfragedatei&lt;/span&gt; auf einen Computer mit Internetzugang.&lt;/p&gt;&lt;p&gt;2. Führen Sie die Anwendung &lt;span style=&quot; font-weight:600;&quot;&gt;Guardant Lizenz-Assistent&lt;/span&gt; darauf aus.&lt;/p&gt;&lt;p&gt;3. Klicken Sie auf «&lt;span style=&quot; font-weight:600;&quot;&gt;Lizenzaktivierung&lt;/span&gt;» und aktualisieren Sie die Lizenz für den anderen Computer.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="../../src/OfflinePageWidget.ui" line="493"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;1. Move the &lt;span style=&quot; font-weight:600;&quot;&gt;rehost file&lt;/span&gt;, recevied from the other computer, and the saved &lt;span style=&quot; font-weight:600;&quot;&gt;fingerprint file&lt;/span&gt;, to the computer with access to the Internet.&lt;/p&gt;&lt;p&gt;2. Run the &lt;span style=&quot; font-weight:600;&quot;&gt;Guardant License Wizard&lt;/span&gt; application on it.&lt;/p&gt;&lt;p&gt;3. Push the «&lt;span style=&quot; font-weight:600;&quot;&gt;License activation&lt;/span&gt;» button and activate a license for another computer.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;1. Übertragen Sie die vom anderen Computer empfangene &lt;span style=&quot; font-weight:600;&quot;&gt;Übertragungsdatei&lt;/span&gt; und die gespeicherte &lt;span style=&quot; font-weight:600;&quot;&gt;Abdruckdatei&lt;/span&gt; auf einen Computer mit Internetzugang.&lt;/p&gt;&lt;p&gt;2. Führen Sie die Anwendung &lt;span style=&quot; font-weight:600;&quot;&gt;Guardant Lizenz-Assistent&lt;/span&gt; darauf aus.&lt;/p&gt;&lt;p&gt;3. Klicken Sie auf «&lt;span style=&quot; font-weight:600;&quot;&gt;Lizenzaktivierung&lt;/span&gt;» und übertragen Sie die Lizenz auf einen anderen Computer.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="../../src/OfflinePageWidget.ui" line="506"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;As a result, you will receive a new &lt;span style=&quot; font-weight:600;&quot;&gt;license file&lt;/span&gt; that you need to activate on this computer.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;So erhalten Sie eine neue &lt;span style=&quot; font-weight:600;&quot;&gt;Lizenzdatei&lt;/span&gt;, die Sie auf diesem Computer aktivieren müssen.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="../../src/OfflinePageWidget.ui" line="537"/>
        <source>Continue, I have the license file</source>
        <translation>Fortfahren, ich habe die Lizenzdatei</translation>
    </message>
    <message>
        <location filename="../../src/OfflinePageWidget.ui" line="590"/>
        <source>Activate with license file</source>
        <translation>Aktivierung mit einer Lizenzdatei</translation>
    </message>
</context>
<context>
    <name>OnlinePageWidget</name>
    <message>
        <location filename="../../src/OnlinePageWidget.ui" line="121"/>
        <source>Serial number</source>
        <translation>Seriennummer</translation>
    </message>
    <message>
        <location filename="../../src/OnlinePageWidget.ui" line="140"/>
        <source>License file or rehost file</source>
        <translation>Lizenz- oder Übertragungsdatei</translation>
    </message>
    <message>
        <location filename="../../src/OnlinePageWidget.ui" line="172"/>
        <source>Offline activation</source>
        <translation>Offline-Aktivierung</translation>
    </message>
    <message>
        <location filename="../../src/OnlinePageWidget.ui" line="277"/>
        <source>Get license</source>
        <translation>Eine Lizenz erhalten</translation>
    </message>
</context>
<context>
    <name>QLineEdit</name>
    <message>
        <location filename="../../src/MainWindow.cpp" line="55"/>
        <source>&amp;Undo</source>
        <translation>Rückgängig</translation>
    </message>
    <message>
        <location filename="../../src/MainWindow.cpp" line="56"/>
        <source>&amp;Redo</source>
        <translation>Wiederholen</translation>
    </message>
    <message>
        <location filename="../../src/MainWindow.cpp" line="57"/>
        <source>Cu&amp;t</source>
        <translation>Ausschneiden</translation>
    </message>
    <message>
        <location filename="../../src/MainWindow.cpp" line="58"/>
        <source>&amp;Copy</source>
        <translation>Kopieren</translation>
    </message>
    <message>
        <location filename="../../src/MainWindow.cpp" line="59"/>
        <source>&amp;Paste</source>
        <translation>Einfügen</translation>
    </message>
    <message>
        <location filename="../../src/MainWindow.cpp" line="60"/>
        <source>Delete</source>
        <translation>Löschen</translation>
    </message>
    <message>
        <location filename="../../src/MainWindow.cpp" line="61"/>
        <source>Select All</source>
        <translation>Alles auswählen</translation>
    </message>
</context>
<context>
    <name>QObject</name>
    <message>
        <location filename="../../src/Common.h" line="29"/>
        <source>Request file</source>
        <translation>Anfragedatei</translation>
    </message>
    <message>
        <location filename="../../src/Common.h" line="31"/>
        <source>License file</source>
        <translation>Lizenzdatei</translation>
    </message>
    <message>
        <location filename="../../src/Common.h" line="33"/>
        <source>Rehost file</source>
        <translation>Übertragungsdatei</translation>
    </message>
    <message>
        <location filename="../../src/Common.h" line="35"/>
        <source>Fingerprint file</source>
        <translation>Abdruckdatei</translation>
    </message>
    <message>
        <location filename="../../src/Common.h" line="46"/>
        <source>Request files</source>
        <translation>Anfragedateien</translation>
    </message>
    <message>
        <location filename="../../src/Common.h" line="49"/>
        <source>License files</source>
        <translation>Lizenzdateien</translation>
    </message>
    <message>
        <location filename="../../src/Common.h" line="52"/>
        <source>Rehost files</source>
        <translation>Übertragungsdateien</translation>
    </message>
    <message>
        <location filename="../../src/Common.h" line="55"/>
        <source>Fingerprint files</source>
        <translation>Abdruckdateien</translation>
    </message>
    <message>
        <location filename="../../src/Common.h" line="66"/>
        <source>License and rehost files</source>
        <translation>Lizenz- oder Übertragungsdateien</translation>
    </message>
    <message>
        <location filename="../../src/Common.h" line="70"/>
        <source>Request and rehost files</source>
        <translation>Anfrage- oder Übertragungsdateien</translation>
    </message>
    <message>
        <location filename="../../src/Common.h" line="77"/>
        <source>All files</source>
        <translation>Alle Dateien</translation>
    </message>
    <message>
        <location filename="../../src/Feature.h" line="29"/>
        <source>Number of launches: </source>
        <translation>Anzahl der Ausführungen: </translation>
    </message>
    <message>
        <location filename="../../src/Feature.h" line="33"/>
        <source>Number of days: </source>
        <translation>Anzahl der Tage: </translation>
    </message>
    <message>
        <location filename="../../src/Feature.h" line="36"/>
        <source>No restrictions</source>
        <translation>Keine Beschränkungen</translation>
    </message>
    <message>
        <location filename="../../src/Feature.h" line="88"/>
        <source>Work station</source>
        <translation>Arbeitsstationen</translation>
    </message>
    <message>
        <location filename="../../src/Feature.h" line="91"/>
        <source>Connection</source>
        <translation>Verbindungen</translation>
    </message>
    <message>
        <location filename="../../src/Feature.h" line="94"/>
        <source>Program copy</source>
        <translation>Kopien des Programms</translation>
    </message>
    <message>
        <location filename="../../src/GrdLicApi.h" line="51"/>
        <source>NO DESCRIPTION</source>
        <translation>OHNE BESCHREIBUNG</translation>
    </message>
    <message>
        <location filename="../../src/GrdLicApi.h" line="55"/>
        <source>serial number</source>
        <translation>Seriennummer</translation>
    </message>
    <message>
        <location filename="../../src/GrdLicApi.h" line="58"/>
        <source>license ID</source>
        <translation>Lizenz-ID</translation>
    </message>
    <message>
        <location filename="../../src/GrdLicApi.h" line="63"/>
        <source>address</source>
        <translation>Adresse</translation>
    </message>
    <message>
        <location filename="../../src/GrdLicApi.h" line="65"/>
        <source>port</source>
        <translation>Port</translation>
    </message>
    <message>
        <location filename="../../src/GrdLicApi.h" line="72"/>
        <source>status code</source>
        <translation>Statuscode</translation>
    </message>
    <message>
        <location filename="../../src/GrdLicApi.h" line="74"/>
        <source>message</source>
        <translation>Nachricht</translation>
    </message>
    <message>
        <location filename="../../src/License.h" line="230"/>
        <source>Key</source>
        <translation>Schlüssel</translation>
    </message>
    <message>
        <location filename="../../src/License.h" line="231"/>
        <source>License</source>
        <translation>Lizenz</translation>
    </message>
    <message>
        <location filename="../../src/MainWindow.cpp" line="149"/>
        <location filename="../../src/MainWindow.cpp" line="208"/>
        <location filename="../../src/MainWindow.cpp" line="283"/>
        <location filename="../../src/MainWindow.cpp" line="344"/>
        <source>Guardant License Wizard</source>
        <translation>Guardant Lizenz-Assistent</translation>
    </message>
    <message>
        <location filename="../../src/MainWindow.cpp" line="158"/>
        <source>File path: </source>
        <translation>Dateipfad: </translation>
    </message>
    <message>
        <location filename="../../src/MainWindow.cpp" line="161"/>
        <source>Domain name: </source>
        <translation>Domänenname: </translation>
    </message>
    <message>
        <location filename="../../src/MainWindow.cpp" line="164"/>
        <source>Host name: </source>
        <translation>Hostname: </translation>
    </message>
    <message>
        <location filename="../../src/MainWindow.cpp" line="209"/>
        <source>finished</source>
        <translation>abgeschlossen</translation>
    </message>
    <message>
        <location filename="../../src/MainWindow.cpp" line="152"/>
        <location filename="../../src/MainWindow.cpp" line="289"/>
        <source> (debug build)</source>
        <translation> (debug build)</translation>
    </message>
    <message>
        <location filename="../../src/MainWindow.cpp" line="154"/>
        <location filename="../../src/MainWindow.cpp" line="291"/>
        <source> (preview build)</source>
        <translation> (preview build)</translation>
    </message>
</context>
<context>
    <name>RehostPageWidget</name>
    <message>
        <location filename="../../src/RehostPageWidget.ui" line="68"/>
        <source>Back</source>
        <translation>Zurück</translation>
    </message>
    <message>
        <location filename="../../src/RehostPageWidget.ui" line="155"/>
        <source>Save</source>
        <translation>Speichern</translation>
    </message>
    <message>
        <location filename="../../src/RehostPageWidget.ui" line="162"/>
        <source>After saving, the license will stop working on this computer</source>
        <translation>Nach dem Speichern funktioniert die Lizenz auf diesem Computer nicht mehr</translation>
    </message>
    <message>
        <location filename="../../src/RehostPageWidget.ui" line="211"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;1. Save the &lt;span style=&quot; font-weight:600;&quot;&gt;rehost file&lt;/span&gt; to a reliable location.&lt;/p&gt;&lt;p&gt;2. Move the &lt;span style=&quot; font-weight:600;&quot;&gt;rehost file&lt;/span&gt; to the new computer and activate it with the &lt;span style=&quot; font-weight:600;&quot;&gt;Guardant License Wizard&lt;/span&gt; application.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;1. Speichern Sie die &lt;span style=&quot; font-weight:600;&quot;&gt;Übertragunsdatei&lt;/span&gt; an einem sicheren Ort.&lt;/p&gt;&lt;p&gt;2. Übertragen Sie die &lt;span style=&quot; font-weight:600;&quot;&gt;Übertragunsdatei&lt;/span&gt; auf den neuen Computer und aktivieren Sie sie in der Anwendung &lt;span style=&quot; font-weight:600;&quot;&gt;Guardant Lizenz-Assistent&lt;/span&gt;.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="../../src/RehostPageWidget.cpp" line="55"/>
        <source>License rehost </source>
        <translation>Lizenzübertragung </translation>
    </message>
</context>
<context>
    <name>RemotePageWidget</name>
    <message>
        <location filename="../../src/RemotePageWidget.ui" line="99"/>
        <source>Receive the request file on the computer where you want to use the software</source>
        <translation>Holen Sie sich die Anfragedatei auf dem Computer, auf dem Sie das Softwareprodukt verwenden möchten</translation>
    </message>
    <message>
        <location filename="../../src/RemotePageWidget.ui" line="139"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;1. Run the &lt;span style=&quot; font-weight:600;&quot;&gt;Guardant License Wizard&lt;/span&gt; application on it.&lt;/p&gt;&lt;p&gt;2. Push the «&lt;span style=&quot; font-weight:600;&quot;&gt;License activation&lt;/span&gt;» button → «&lt;span style=&quot; font-weight:600;&quot;&gt;Use on this computer&lt;/span&gt;» → «&lt;span style=&quot; font-weight:600;&quot;&gt;Offline activation&lt;/span&gt;».&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;1. Führen Sie die Anwendung &lt;span style=&quot; font-weight:600;&quot;&gt;Guardant Lizenz-Assistent&lt;/span&gt; darauf aus.&lt;/p&gt;&lt;p&gt;2. Klicken Sie auf «&lt;span style=&quot; font-weight:600;&quot;&gt;Lizenzaktivierung&lt;/span&gt;» → «&lt;span style=&quot; font-weight:600;&quot;&gt;Auf diesem Computer verwenden&lt;/span&gt;» → «&lt;span style=&quot; font-weight:600;&quot;&gt;Offline-Aktivierung&lt;/span&gt;».&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="../../src/RemotePageWidget.ui" line="149"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;As a result, you will receive a &lt;span style=&quot; font-weight:600;&quot;&gt;request file&lt;/span&gt; that you need to use on this or any other computer with access to the Internet.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Das Ergebnis ist eine &lt;span style=&quot; font-weight:600;&quot;&gt;Anfragedatei&lt;/span&gt;, die Sie auf diesem oder einem anderen Computer mit Internetzugang verwenden sollten.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="../../src/RemotePageWidget.ui" line="180"/>
        <source>Continue</source>
        <translation>Fortfahren</translation>
    </message>
    <message>
        <location filename="../../src/RemotePageWidget.ui" line="248"/>
        <source>License activation for another computer</source>
        <translation>Aktivieren der Lizenz für einen anderen Computer</translation>
    </message>
    <message>
        <location filename="../../src/RemotePageWidget.ui" line="403"/>
        <source>Activate a new license</source>
        <translation>Eine neue Lizenz aktivieren</translation>
    </message>
    <message>
        <location filename="../../src/RemotePageWidget.ui" line="416"/>
        <source>Update this license</source>
        <translation>Diese Lizenz erneuern</translation>
    </message>
    <message>
        <location filename="../../src/RemotePageWidget.ui" line="429"/>
        <source>Rehost this license</source>
        <translation>Diese Lizenz übertragen</translation>
    </message>
    <message>
        <location filename="../../src/RemotePageWidget.ui" line="516"/>
        <source>Ready</source>
        <translation>Fertig</translation>
    </message>
    <message>
        <location filename="../../src/RemotePageWidget.ui" line="637"/>
        <source>Save</source>
        <translation>Speichern</translation>
    </message>
    <message>
        <location filename="../../src/RemotePageWidget.ui" line="647"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Send the received &lt;span style=&quot; font-weight:600;&quot;&gt;license file&lt;/span&gt; to the computer where you want to use the software.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Senden Sie die erhaltene &lt;span style=&quot; font-weight:600;&quot;&gt;Lizenzdatei&lt;/span&gt; an den Computer, auf dem Sie das Softwareprodukt verwenden möchten.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="../../src/RemotePageWidget.ui" line="657"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;1. Run the &lt;span style=&quot; font-weight:600;&quot;&gt;Guardant License Wizard&lt;/span&gt; application on the computer where you want to use the software.&lt;/p&gt;&lt;p&gt;2. Push the «&lt;span style=&quot; font-weight:600;&quot;&gt;License activation&lt;/span&gt;» button → «&lt;span style=&quot; font-weight:600;&quot;&gt;Use on this computer&lt;/span&gt;» → «&lt;span style=&quot; font-weight:600;&quot;&gt;Offline activation&lt;/span&gt;».&lt;/p&gt;&lt;p&gt;3. Select the received &lt;span style=&quot; font-weight:600;&quot;&gt;license file&lt;/span&gt;.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;1. Führen Sie die Anwendung &lt;span style=&quot; font-weight:600;&quot;&gt;Guardant Lizenz-Assistent&lt;/span&gt; auf dem Computer aus, auf dem das Softwareprodukt verwendet werden soll.&lt;/p&gt;&lt;p&gt;2. Klicken Sie auf «&lt;span style=&quot; font-weight:600;&quot;&gt;Lizenzaktivierung&lt;/span&gt;» → «&lt;span style=&quot; font-weight:600;&quot;&gt;Auf diesem Computer verwenden&lt;/span&gt;» → «&lt;span style=&quot; font-weight:600;&quot;&gt;Offline-Aktivierung&lt;/span&gt;».&lt;/p&gt;&lt;p&gt;3. Wählen Sie die resultierende &lt;span style=&quot; font-weight:600;&quot;&gt;Lizenzdatei&lt;/span&gt;.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
</context>
<context>
    <name>SettingsPageWidget</name>
    <message>
        <location filename="../../src/SettingsPageWidget.ui" line="62"/>
        <source>Back</source>
        <translation>Zurück</translation>
    </message>
    <message>
        <location filename="../../src/SettingsPageWidget.ui" line="75"/>
        <source>Settings</source>
        <translation>Einstellungen</translation>
    </message>
    <message>
        <location filename="../../src/SettingsPageWidget.ui" line="165"/>
        <source>License server address</source>
        <translation>Lizenzserveradresse</translation>
    </message>
    <message>
        <location filename="../../src/SettingsPageWidget.ui" line="184"/>
        <source>Required for the license activation, installation and update</source>
        <translation>Erforderlich für die Aktivierung, Installation und Aktualisierung von Lizenzen</translation>
    </message>
    <message>
        <location filename="../../src/SettingsPageWidget.ui" line="249"/>
        <source>Automatically check license updates on startup</source>
        <translation>Beim Start automatisch nach Lizenzaktualisierungen suchen</translation>
    </message>
    <message>
        <location filename="../../src/SettingsPageWidget.ui" line="350"/>
        <source>Go to log directory</source>
        <translation>Weiter zur Logdatei</translation>
    </message>
</context>
<context>
    <name>WriteOncePageWidget</name>
    <message>
        <location filename="../../src/WriteOncePageWidget.ui" line="62"/>
        <source>Back</source>
        <translation>Zurück</translation>
    </message>
    <message>
        <location filename="../../src/WriteOncePageWidget.ui" line="91"/>
        <source>The old license will be erased from the key on writing</source>
        <translation>Die alte Lizenz wird gelöscht, wenn die neue Lizenz auf den Schlüssel geschrieben wird</translation>
    </message>
    <message>
        <location filename="../../src/WriteOncePageWidget.ui" line="189"/>
        <source>Code for the license writing</source>
        <translation>Code für die Erfassung einer Lizenz</translation>
    </message>
    <message>
        <location filename="../../src/WriteOncePageWidget.ui" line="211"/>
        <source>File with codes</source>
        <translation>Code-Datei</translation>
    </message>
    <message>
        <location filename="../../src/WriteOncePageWidget.ui" line="381"/>
        <source>Write</source>
        <translation>Schreiben</translation>
    </message>
    <message>
        <location filename="../../src/WriteOncePageWidget.cpp" line="140"/>
        <source>Write a license to the Guardant %1 key #%2</source>
        <translation>Schreiben einer Lizenz auf einen Guardant-Schlüssel %1 #%2</translation>
    </message>
</context>
<context>
    <name>WriteSomePageWidget</name>
    <message>
        <location filename="../../src/WriteSomePageWidget.ui" line="62"/>
        <source>Back</source>
        <translation>Zurück</translation>
    </message>
    <message>
        <location filename="../../src/WriteSomePageWidget.ui" line="78"/>
        <source>Write a license to a key</source>
        <translation>Schreiben einer Lizenz auf einen Schlüssel</translation>
    </message>
    <message>
        <location filename="../../src/WriteSomePageWidget.ui" line="94"/>
        <source>The old license will be erased from the key on writing</source>
        <translation>Die alte Lizenz wird gelöscht, wenn die neue Lizenz auf den Schlüssel geschrieben wird</translation>
    </message>
    <message>
        <location filename="../../src/WriteSomePageWidget.ui" line="193"/>
        <source>Insert a USB key to write a license</source>
        <translation>Stecken Sie den USB-Stick ein, um die Lizenz zu speichern</translation>
    </message>
    <message>
        <location filename="../../src/WriteSomePageWidget.ui" line="212"/>
        <source>Refresh</source>
        <translation>Erneuern</translation>
    </message>
    <message>
        <location filename="../../src/WriteSomePageWidget.cpp" line="350"/>
        <source>Write</source>
        <translation>Schreiben</translation>
    </message>
</context>
</TS>
