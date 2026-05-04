<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.1" language="es_ES">
<context>
    <name>ActivationPageWidget</name>
    <message>
        <location filename="../../src/ActivationPageWidget.ui" line="68"/>
        <source>Back</source>
        <translation>Atrás</translation>
    </message>
    <message>
        <location filename="../../src/ActivationPageWidget.ui" line="81"/>
        <source>License activation</source>
        <translation>Activación de la licencia</translation>
    </message>
    <message>
        <location filename="../../src/ActivationPageWidget.ui" line="94"/>
        <source>For serial number activation a computer with access to the Internet is needed</source>
        <translation>Para activar el número de serie, necesitará una computadora con acceso a Internet</translation>
    </message>
    <message>
        <location filename="../../src/ActivationPageWidget.ui" line="214"/>
        <source>On which computer do you want to use the license?</source>
        <translation>¿En qué computadora desea utilizar la licencia?</translation>
    </message>
    <message>
        <location filename="../../src/ActivationPageWidget.ui" line="234"/>
        <source>On this</source>
        <translation>Aquí</translation>
    </message>
    <message>
        <location filename="../../src/ActivationPageWidget.ui" line="259"/>
        <source>On another</source>
        <translation>En otra computadora</translation>
    </message>
    <message>
        <location filename="../../src/ActivationPageWidget.ui" line="284"/>
        <source>Write a license to a USB key to use it on any computer</source>
        <translation>Escriba la licencia en una llave USB para usar en cualquier computadora</translation>
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
        <translation>Uso:
license_wizard
    ejecutar en modo gráfico
license_wizard --help
    mostrar este mensaje de referencia
license_wizard --console &lt;operación&gt;&lt;argumentos&gt;
    ejecutar en modo consola, aplicar la operación especificada con los
        argumentos espesificadas

Operaciones y sus argumentos:
--list
    mostrar la lista de licencias
--activate &lt;número_de_serie&gt; --host &lt;url&gt;
    activar con número de serie
--update &lt;ID_de_licencia&gt; --host &lt;url&gt;
    actualizar la licencia especificada
--activate-request &lt;ruta_de_archivo_de_solicitud&gt;
    crear solicitud de activación
--update-request &lt;ID_de_licencia&gt;&lt;ruta_de_archivo_de_solicitud&gt;
    crear solicitud para actualizar la licencia especificada
--activate-response &lt;número_de_serie&gt;&lt;ruta_de_archivo_de_solicitud&gt;
        &lt;ruta_de_archivo_de_licencia&gt; --host &lt;url&gt;
    enviar solicitud de activación
--update-response &lt;ruta_de_archivo_de_solicitud&gt;&lt;ruta_de_archivo_de_licencia&gt; --host &lt;url&gt;
    enviar solicitud de actualización
--activate-offline &lt;ruta_de_archivo_de_licencia&gt;
    activar con el archivo de licencia
--update-offline &lt;ruta_de_archivo_de_licencia&gt;
    actualizar con el archivo de licencia
--rehost-extract &lt;ID_de_licencia&gt; &lt;ruta_de_archivo_de_transferencia&gt;
    extraer la licencia para transferencia
--rehost &lt;ruta_de_archivo_de_transferencia&gt; --host &lt;url&gt;
    transferir la licencia especificada
--rehost-request &lt;ruta_de_archivo_de_huellas&gt;
    crear solicitud de transferencia
--rehost-response &lt;ruta_de_archivo_de_transferencia&gt;&lt;ruta_de_archivo_de_huellas&gt;
        &lt;ruta_de_archivo_de_licencia&gt; --host &lt;url&gt;
    enviar solicitud de transferencia
--rehost-offline &lt;ruta_de_archivo_de_licencia&gt;
    transferir con el archivo de licencia
--dongle-set-license &lt;dongle_ID&gt; &lt;serial_number&gt; --host &lt;url&gt;
    activar en la clave especificada con el número de serie
--dongle-blink &lt;dongle_ID&gt;
    activar el parpadeo del LED en la clave especificada
</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="168"/>
        <source>License activation</source>
        <translation>Activación de la licencia</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="171"/>
        <source>License update</source>
        <translation>Actualización de la licencia</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="173"/>
        <source>License activation request creation</source>
        <translation>Creación de una solicitud de activación de licencia</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="175"/>
        <source>License update request creation</source>
        <translation>Creación de una solicitud de actualización de licencia</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="177"/>
        <source>License activation request sending</source>
        <translation>Envío de una solicitud de activación de licencia</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="179"/>
        <source>License update request sending</source>
        <translation>Envío de una solicitud de actualización de licencia</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="181"/>
        <source>License rehost request creation</source>
        <translation>Creación de una solicitud de transferencia de licencia</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="183"/>
        <source>License extraction</source>
        <translation>Extracción de licencia</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="186"/>
        <source>License rehost</source>
        <translation>Transferencia de licencia</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="188"/>
        <source>License rehost request sending</source>
        <translation>Envío de una solicitud de transferencia de licencia</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="190"/>
        <source>Setting license to the key</source>
        <translation>Activación de la licencia de clave</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="195"/>
        <source>Unexpected operation</source>
        <translation>Operación inesperada</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="301"/>
        <source>Incorrect license ID format
Expected 0xNNNNNNNN, where each N is a hexadecimal digit</source>
        <translation>Formato de ID de licencia no válido
Se espera 0xNNNNNNNNN, donde cada carácter N es un dígito hexadecimal</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="306"/>
        <source>Incorrect dongle ID format
Expected 0xNNNNNNNN, where each N is a hexadecimal digit</source>
        <translation>Formato de ID de clave no válido
Se espera 0xNNNNNNNNN, donde cada carácter N es un dígito hexadecimal</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="311"/>
        <source>Incorrect serial number format
Expected NNNNNN-NNNNNN-NNNNNN-NNNNNN-NNNNNN, where each N is a Latin letter in upper or lower case or a digit</source>
        <translation>Formato de número de serie no válido
Se espera NNNNNN-NNNNNN-NNNNNN-NNNNNN-NNNNNN, donde cada carácter N es donde cada carácter N es una letra mayúscula o minúscula del alfabeto latino o un número</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="316"/>
        <source>File not found: %1</source>
        <translation>Archivo no encontrado: %1</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="319"/>
        <source>Incorrect host URL format</source>
        <translation>Formato de dirección de servidor es incorrecto</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="322"/>
        <source>Incorrect file path</source>
        <translation>Ruta al archivo es incorrecta</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="328"/>
        <location filename="../../src/CommandLineManager.cpp" line="337"/>
        <location filename="../../src/CommandLineManager.cpp" line="430"/>
        <source>Internal error</source>
        <translation>Error interno</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="346"/>
        <source>%1 completed</source>
        <translation>%1 completado(-a/-o)</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="408"/>
        <source>Option %1 must go first</source>
        <translation>La opción %1 debe seguir la primera</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="412"/>
        <source>Option %1 must go last</source>
        <translation>La opción %1 debe seguir la última</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="416"/>
        <source>Incorrect number of arguments</source>
        <translation>Número de argumentos está incorrecto</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="419"/>
        <source>Option %1 has incorrect value</source>
        <translation>La opción %1 tiene un valor incorrecto</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="423"/>
        <source>Parameter has incorrect value</source>
        <translation>El parámetro tiene un valor incorrecto</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="426"/>
        <source>Unrecognized operation</source>
        <translation>Operación no identificada</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="456"/>
        <source>No licenses installed!</source>
        <translation>¡No hay licencias instaladas!</translation>
    </message>
</context>
<context>
    <name>DonglePageWidget</name>
    <message>
        <location filename="../../src/DonglePageWidget.ui" line="124"/>
        <source>Code for the license writing</source>
        <translation>Código de registro de licencia</translation>
    </message>
    <message>
        <location filename="../../src/DonglePageWidget.ui" line="143"/>
        <source>File with codes</source>
        <translation>Archivo de códigos</translation>
    </message>
    <message>
        <location filename="../../src/DonglePageWidget.ui" line="267"/>
        <source>Continue</source>
        <translation>Continuar</translation>
    </message>
</context>
<context>
    <name>FilePickingWidget</name>
    <message>
        <location filename="../../src/FilePickingWidget.ui" line="44"/>
        <source>Select a file, which you received as a result of an activation, an update or a rehost from another computer.</source>
        <translation>Seleccione el archivo que recibió al activar, actualizar o transferir la licencia desde otra computadora.</translation>
    </message>
    <message>
        <location filename="../../src/FilePickingWidget.ui" line="60"/>
        <source>Select a fingerprint file, which you recevied from the computer, where you want to rehost the license to.</source>
        <translation>Seleccione el archivo de huella que recibió de la computadora al que desea transferir la licencia.</translation>
    </message>
    <message>
        <location filename="../../src/FilePickingWidget.ui" line="70"/>
        <source>Select a file with codes for writing a license to the key.</source>
        <translation>Seleccione el archivo de códigos para escribir licencias.</translation>
    </message>
    <message>
        <location filename="../../src/FilePickingWidget.ui" line="89"/>
        <source>Select a file</source>
        <translation>Seleccionar un archivo</translation>
    </message>
    <message>
        <location filename="../../src/FilePickingWidget.ui" line="202"/>
        <source>Incorrect file</source>
        <translation>Archivo incorrecto</translation>
    </message>
    <message>
        <location filename="../../src/FilePickingWidget.ui" line="222"/>
        <source>Select another one</source>
        <translation>Seleccionar otro</translation>
    </message>
    <message>
        <location filename="../../src/FilePickingWidget.cpp" line="233"/>
        <source>There are %1 codes (keys) in this file</source>
        <translation>El archivo contiene %1 de códigos (claves)</translation>
    </message>
</context>
<context>
    <name>LicenseItemWidget</name>
    <message>
        <location filename="../../src/LicenseItemWidget.ui" line="82"/>
        <source>Trial Software Key</source>
        <translation>Clave de prueba del software</translation>
    </message>
    <message>
        <location filename="../../src/LicenseItemWidget.ui" line="110"/>
        <source>Vendor code</source>
        <translation>Código de acceso</translation>
    </message>
    <message>
        <location filename="../../src/LicenseItemWidget.ui" line="197"/>
        <source>Update license</source>
        <translation>Instalar actualización</translation>
    </message>
    <message>
        <location filename="../../src/LicenseItemWidget.ui" line="239"/>
        <source>Check updates</source>
        <translation>Buscar actualizaciones</translation>
    </message>
    <message>
        <location filename="../../src/LicenseItemWidget.ui" line="244"/>
        <source>Offline update</source>
        <translation>Actualización sin conexión</translation>
    </message>
    <message>
        <location filename="../../src/LicenseItemWidget.ui" line="249"/>
        <source>Move to another computer</source>
        <translation>Transferir a otra computadora</translation>
    </message>
    <message>
        <location filename="../../src/LicenseItemWidget.ui" line="254"/>
        <source>Remove</source>
        <translation>Eliminar</translation>
    </message>
    <message>
        <location filename="../../src/LicenseItemWidget.ui" line="259"/>
        <source>Write a license to this key</source>
        <translation>Escribir la licencia en esta clave</translation>
    </message>
</context>
<context>
    <name>LicensePickingWidget</name>
    <message>
        <location filename="../../src/LicensePickingWidget.ui" line="44"/>
        <source>Select the license</source>
        <translation>Seleccione una licencia</translation>
    </message>
    <message>
        <location filename="../../src/LicensePickingWidget.ui" line="176"/>
        <source>No licenses installed</source>
        <translation>No hay licencias instaladas</translation>
    </message>
    <message>
        <location filename="../../src/LicensePickingWidget.cpp" line="309"/>
        <source>Select</source>
        <translation>Seleccionar</translation>
    </message>
</context>
<context>
    <name>ListPageWidget</name>
    <message>
        <location filename="../../src/ListPageWidget.ui" line="71"/>
        <source>Licenses</source>
        <translation>Licencias</translation>
    </message>
    <message>
        <location filename="../../src/ListPageWidget.ui" line="91"/>
        <source>License activation</source>
        <translation>Activación de la licencia</translation>
    </message>
    <message>
        <location filename="../../src/ListPageWidget.ui" line="135"/>
        <source>No license found on this computer</source>
        <translation>No se encontró ninguna licencia en esta computadora</translation>
    </message>
    <message>
        <location filename="../../src/ListPageWidget.ui" line="178"/>
        <source>What do you have?</source>
        <translation>¿Qué tiene?</translation>
    </message>
    <message>
        <location filename="../../src/ListPageWidget.ui" line="207"/>
        <source>Serial number, license file</source>
        <translation>número de serie, archivo de licencia</translation>
    </message>
    <message>
        <location filename="../../src/ListPageWidget.ui" line="220"/>
        <source>Activate a license</source>
        <translation>Active la licencia</translation>
    </message>
    <message>
        <location filename="../../src/ListPageWidget.ui" line="233"/>
        <source>USB key</source>
        <translation>llave USB</translation>
    </message>
    <message>
        <location filename="../../src/ListPageWidget.ui" line="246"/>
        <source>Insert it in this computer</source>
        <translation>Insértelo en esta computadora</translation>
    </message>
    <message>
        <location filename="../../src/ListPageWidget.ui" line="292"/>
        <source>Licensing
terms</source>
        <translation>Restricción
de la licencia</translation>
    </message>
    <message>
        <location filename="../../src/ListPageWidget.ui" line="298"/>
        <source>Concurrent
instances</source>
        <translation>Recurso
de red</translation>
    </message>
    <message>
        <location filename="../../src/ListPageWidget.ui" line="304"/>
        <source>VM
enabled</source>
        <translation>Trabajo
en VM</translation>
    </message>
    <message>
        <location filename="../../src/ListPageWidget.cpp" line="587"/>
        <source>The number of machines on which the Feature is running simultaneously</source>
        <translation>Número de máquinas que ejecutan el Componente simultáneamente</translation>
    </message>
    <message>
        <location filename="../../src/ListPageWidget.cpp" line="590"/>
        <source>The number of API connections</source>
        <translation>Número de conexiones a la API</translation>
    </message>
    <message>
        <location filename="../../src/ListPageWidget.cpp" line="592"/>
        <source>The number of running instances of the Feature</source>
        <translation>Número de instancias del Componente ejecutadas</translation>
    </message>
</context>
<context>
    <name>MainPageWidget</name>
    <message>
        <location filename="../../src/MainPageWidget.ui" line="83"/>
        <source>Settings</source>
        <translation>Configuración</translation>
    </message>
    <message>
        <location filename="../../src/MainPageWidget.cpp" line="286"/>
        <location filename="../../src/MainPageWidget.cpp" line="310"/>
        <source>Internal error</source>
        <translation>Error interno</translation>
    </message>
    <message>
        <location filename="../../src/MainPageWidget.cpp" line="288"/>
        <source>License installed</source>
        <translation>Licencia está instalada</translation>
    </message>
    <message>
        <location filename="../../src/MainPageWidget.cpp" line="290"/>
        <source>License updated</source>
        <translation>Licencia está actualizada</translation>
    </message>
    <message>
        <location filename="../../src/MainPageWidget.cpp" line="292"/>
        <source>License update available</source>
        <translation>Actualización de la licencia está disponible</translation>
    </message>
    <message>
        <location filename="../../src/MainPageWidget.cpp" line="294"/>
        <source>Licenses updates available</source>
        <translation>Actualización de las licencias está disponible</translation>
    </message>
    <message>
        <location filename="../../src/MainPageWidget.cpp" line="296"/>
        <source>No more license updates</source>
        <translation>No hay actualizaciones para las licencias</translation>
    </message>
    <message>
        <location filename="../../src/MainPageWidget.cpp" line="298"/>
        <source>Unable to check license updates</source>
        <translation>No se pudo buscar actualizaciones</translation>
    </message>
    <message>
        <location filename="../../src/MainPageWidget.cpp" line="300"/>
        <source>Unable to check licenses updates</source>
        <translation>No se pudo buscar actualizaciones</translation>
    </message>
    <message>
        <location filename="../../src/MainPageWidget.cpp" line="302"/>
        <source>Unable to update the license</source>
        <translation>No se pudo actualizar la licencia</translation>
    </message>
    <message>
        <location filename="../../src/MainPageWidget.cpp" line="304"/>
        <source>License extracted</source>
        <translation>La licencia está extraída</translation>
    </message>
    <message>
        <location filename="../../src/MainPageWidget.cpp" line="314"/>
        <source>License ID copied to clipboard</source>
        <translation>ID de licencia copiado al portapapeles</translation>
    </message>
</context>
<context>
    <name>MainWindow</name>
    <message>
        <location filename="../../src/MainWindow.cpp" line="345"/>
        <source>Entered data is not URL</source>
        <translation>Los datos ingresados no son la dirección URL</translation>
    </message>
</context>
<context>
    <name>OfflinePageWidget</name>
    <message>
        <location filename="../../src/OfflinePageWidget.ui" line="84"/>
        <source>Offline activation</source>
        <translation>Activación sin conexión</translation>
    </message>
    <message>
        <location filename="../../src/OfflinePageWidget.ui" line="177"/>
        <source>New license</source>
        <translation>Licencia nueva</translation>
    </message>
    <message>
        <location filename="../../src/OfflinePageWidget.ui" line="196"/>
        <source>License update</source>
        <translation>Actualización de la licencia</translation>
    </message>
    <message>
        <location filename="../../src/OfflinePageWidget.ui" line="215"/>
        <source>License rehost</source>
        <translation>Transferencia de licencia</translation>
    </message>
    <message>
        <location filename="../../src/OfflinePageWidget.ui" line="274"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Save the &lt;span style=&quot; font-weight:600;&quot;&gt;fingerprint file&lt;/span&gt;. It contains info for license rehost with the help of another computer with access to the Internet.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Guarde&lt;span style=&quot; font-weight:600;&quot;&gt;archivo de huella&lt;/span&gt;. Contiene información para transferir la licencia a través de otra computadora con acceso a Internet.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="../../src/OfflinePageWidget.ui" line="284"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Save the &lt;span style=&quot; font-weight:600;&quot;&gt;request file&lt;/span&gt;. It contains info for license activation on another computer with access to the Internet.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Guarde&lt;span style=&quot; font-weight:600;&quot;&gt;archivo de solicitud&lt;/span&gt;. Contiene información para activar la licencia en otra computadora con acceso a Internet.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="../../src/OfflinePageWidget.ui" line="381"/>
        <source>Save</source>
        <translation>Guardar</translation>
    </message>
    <message>
        <location filename="../../src/OfflinePageWidget.ui" line="412"/>
        <source>Continue</source>
        <translation>Continuar</translation>
    </message>
    <message>
        <location filename="../../src/OfflinePageWidget.ui" line="473"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;1. Move the saved &lt;span style=&quot; font-weight:600;&quot;&gt;request file&lt;/span&gt; and &lt;span style=&quot; font-weight:600;&quot;&gt;serial number&lt;/span&gt; to the computer with access to the Internet.&lt;/p&gt;&lt;p&gt;2. Run the &lt;span style=&quot; font-weight:600;&quot;&gt;Guardant License Wizard&lt;/span&gt; application on it.&lt;/p&gt;&lt;p&gt;3. Push the «&lt;span style=&quot; font-weight:600;&quot;&gt;License activation&lt;/span&gt;» button and activate a license for another computer.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;1. Transfiera el &lt;span style=&quot; font-weight:600;&quot;&gt;archivo de solicitud&lt;/span&gt; y el &lt;span style=&quot; font-weight:600;&quot;&gt;número de serie&lt;/span&gt; guardados a una computadora con acceso a Internet.&lt;/p&gt;&lt;p&gt;2. Ejecute la aplicación en esta computadora &lt;span style=&quot; font-weight:600;&quot;&gt;Asistente de licencias Guardant&lt;/span&gt;.&lt;/p&gt;&lt;p&gt;3. Haga clic en el botón «&lt;span style=&quot; font-weight:600;&quot;&gt;Activación de la licencia&lt;/span&gt;» y active la licencia para otra computadora.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="../../src/OfflinePageWidget.ui" line="483"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;1. Move the saved &lt;span style=&quot; font-weight:600;&quot;&gt;request file&lt;/span&gt; to the computer with access to the Internet.&lt;/p&gt;&lt;p&gt;2. Run the &lt;span style=&quot; font-weight:600;&quot;&gt;Guardant License Wizard&lt;/span&gt; application on it.&lt;/p&gt;&lt;p&gt;3. Push the «&lt;span style=&quot; font-weight:600;&quot;&gt;License activation&lt;/span&gt;» button and update a license for another computer.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;1. Transfiera el &lt;span style=&quot; font-weight:600;&quot;&gt;archivo de solicitud&lt;/span&gt; guardado a una computadora con acceso a Internet.&lt;/p&gt;&lt;p&gt;2. Ejecute la aplicación en esta computadora &lt;span style=&quot; font-weight:600;&quot;&gt;Asistente de licencias Guardant&lt;/span&gt;.&lt;/p&gt;&lt;p&gt;3. Haga clic en el botón «&lt;span style=&quot; font-weight:600;&quot;&gt;Activación de la licencia&lt;/span&gt;» y actualice la licencia para otra computadora.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="../../src/OfflinePageWidget.ui" line="493"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;1. Move the &lt;span style=&quot; font-weight:600;&quot;&gt;rehost file&lt;/span&gt;, recevied from the other computer, and the saved &lt;span style=&quot; font-weight:600;&quot;&gt;fingerprint file&lt;/span&gt;, to the computer with access to the Internet.&lt;/p&gt;&lt;p&gt;2. Run the &lt;span style=&quot; font-weight:600;&quot;&gt;Guardant License Wizard&lt;/span&gt; application on it.&lt;/p&gt;&lt;p&gt;3. Push the «&lt;span style=&quot; font-weight:600;&quot;&gt;License activation&lt;/span&gt;» button and activate a license for another computer.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;1. Transfiera el &lt;span style=&quot; font-weight:600;&quot;&gt; archivo de transferencia&lt;/span&gt;obtenido de otra computadora y guardado &lt;span style=&quot; font-weight:600;&quot;&gt; archivo de huella&lt;/span&gt; a una computadora con acceso a Internet.&lt;/p&gt;&lt;p&gt;2. Ejecute la aplicación en esta computadora &lt;span style=&quot; font-weight:600;&quot;&gt;Asistente de licencias Guardant&lt;/span&gt;.&lt;/p&gt;&lt;p&gt;3. Haga clic en el botón «&lt;span style=&quot; font-weight:600;&quot;&gt;Activación de la licencia&lt;/span&gt;» y transfiera la licencia a otra computadora.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="../../src/OfflinePageWidget.ui" line="506"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;As a result, you will receive a new &lt;span style=&quot; font-weight:600;&quot;&gt;license file&lt;/span&gt; that you need to activate on this computer.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Como resultado, obtendrá un archivo &lt;span style=&quot; font-weight:600;&quot;&gt; nuevo  de licencia&lt;/span&gt; que debe activarse en esta computadora.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="../../src/OfflinePageWidget.ui" line="537"/>
        <source>Continue, I have the license file</source>
        <translation>Continuar, tengo un archivo de licencia</translation>
    </message>
    <message>
        <location filename="../../src/OfflinePageWidget.ui" line="590"/>
        <source>Activate with license file</source>
        <translation>Activación con el archivo de licencia</translation>
    </message>
</context>
<context>
    <name>OnlinePageWidget</name>
    <message>
        <location filename="../../src/OnlinePageWidget.ui" line="121"/>
        <source>Serial number</source>
        <translation>Número de serie</translation>
    </message>
    <message>
        <location filename="../../src/OnlinePageWidget.ui" line="140"/>
        <source>License file or rehost file</source>
        <translation>Archivo de licencia o archivo de transferencia</translation>
    </message>
    <message>
        <location filename="../../src/OnlinePageWidget.ui" line="172"/>
        <source>Offline activation</source>
        <translation>Activación sin conexión</translation>
    </message>
    <message>
        <location filename="../../src/OnlinePageWidget.ui" line="277"/>
        <source>Get license</source>
        <translation>Obtener una licencia</translation>
    </message>
</context>
<context>
    <name>QLineEdit</name>
    <message>
        <location filename="../../src/MainWindow.cpp" line="55"/>
        <source>&amp;Undo</source>
        <translation>Deshacer</translation>
    </message>
    <message>
        <location filename="../../src/MainWindow.cpp" line="56"/>
        <source>&amp;Redo</source>
        <translation>Rehacer</translation>
    </message>
    <message>
        <location filename="../../src/MainWindow.cpp" line="57"/>
        <source>Cu&amp;t</source>
        <translation>Cortar</translation>
    </message>
    <message>
        <location filename="../../src/MainWindow.cpp" line="58"/>
        <source>&amp;Copy</source>
        <translation>Copiar</translation>
    </message>
    <message>
        <location filename="../../src/MainWindow.cpp" line="59"/>
        <source>&amp;Paste</source>
        <translation>Pegar</translation>
    </message>
    <message>
        <location filename="../../src/MainWindow.cpp" line="60"/>
        <source>Delete</source>
        <translation>Eliminar</translation>
    </message>
    <message>
        <location filename="../../src/MainWindow.cpp" line="61"/>
        <source>Select All</source>
        <translation>Seleccionar todo</translation>
    </message>
</context>
<context>
    <name>QObject</name>
    <message>
        <location filename="../../src/Common.h" line="29"/>
        <source>Request file</source>
        <translation>Archivo de solicitud</translation>
    </message>
    <message>
        <location filename="../../src/Common.h" line="31"/>
        <source>License file</source>
        <translation>Archivo de licencia</translation>
    </message>
    <message>
        <location filename="../../src/Common.h" line="33"/>
        <source>Rehost file</source>
        <translation>Archivo de transferencia</translation>
    </message>
    <message>
        <location filename="../../src/Common.h" line="35"/>
        <source>Fingerprint file</source>
        <translation>Archivo de huella</translation>
    </message>
    <message>
        <location filename="../../src/Common.h" line="46"/>
        <source>Request files</source>
        <translation>Archivos de solicitudes</translation>
    </message>
    <message>
        <location filename="../../src/Common.h" line="49"/>
        <source>License files</source>
        <translation>Archivos de licencias</translation>
    </message>
    <message>
        <location filename="../../src/Common.h" line="52"/>
        <source>Rehost files</source>
        <translation>Archivos de transferencias</translation>
    </message>
    <message>
        <location filename="../../src/Common.h" line="55"/>
        <source>Fingerprint files</source>
        <translation>Archivos de huellas</translation>
    </message>
    <message>
        <location filename="../../src/Common.h" line="66"/>
        <source>License and rehost files</source>
        <translation>Archivos de licencias y transferencias</translation>
    </message>
    <message>
        <location filename="../../src/Common.h" line="70"/>
        <source>Request and rehost files</source>
        <translation>Archivos de solicitudes y transferencias</translation>
    </message>
    <message>
        <location filename="../../src/Common.h" line="77"/>
        <source>All files</source>
        <translation>Todos archivos</translation>
    </message>
    <message>
        <location filename="../../src/Feature.h" line="29"/>
        <source>Number of launches: </source>
        <translation>Número de inicios: </translation>
    </message>
    <message>
        <location filename="../../src/Feature.h" line="33"/>
        <source>Number of days: </source>
        <translation>Número de días: </translation>
    </message>
    <message>
        <location filename="../../src/Feature.h" line="36"/>
        <source>No restrictions</source>
        <translation>Sin restricciones</translation>
    </message>
    <message>
        <location filename="../../src/Feature.h" line="88"/>
        <source>Work station</source>
        <translation>Estaciones de trabajo</translation>
    </message>
    <message>
        <location filename="../../src/Feature.h" line="91"/>
        <source>Connection</source>
        <translation>Conexiones</translation>
    </message>
    <message>
        <location filename="../../src/Feature.h" line="94"/>
        <source>Program copy</source>
        <translation>Copias del programa</translation>
    </message>
    <message>
        <location filename="../../src/GrdLicApi.h" line="51"/>
        <source>NO DESCRIPTION</source>
        <translation>SIN DESCRIPCIÓN</translation>
    </message>
    <message>
        <location filename="../../src/GrdLicApi.h" line="55"/>
        <source>serial number</source>
        <translation>número de serie</translation>
    </message>
    <message>
        <location filename="../../src/GrdLicApi.h" line="58"/>
        <source>license ID</source>
        <translation>ID de licencia</translation>
    </message>
    <message>
        <location filename="../../src/GrdLicApi.h" line="63"/>
        <source>address</source>
        <translation>Dirección</translation>
    </message>
    <message>
        <location filename="../../src/GrdLicApi.h" line="65"/>
        <source>port</source>
        <translation>puerto</translation>
    </message>
    <message>
        <location filename="../../src/GrdLicApi.h" line="72"/>
        <source>status code</source>
        <translation>código del estado</translation>
    </message>
    <message>
        <location filename="../../src/GrdLicApi.h" line="74"/>
        <source>message</source>
        <translation>mensaje</translation>
    </message>
    <message>
        <location filename="../../src/License.h" line="230"/>
        <source>Key</source>
        <translation>Clave</translation>
    </message>
    <message>
        <location filename="../../src/License.h" line="231"/>
        <source>License</source>
        <translation>Licencia</translation>
    </message>
    <message>
        <location filename="../../src/MainWindow.cpp" line="149"/>
        <location filename="../../src/MainWindow.cpp" line="208"/>
        <location filename="../../src/MainWindow.cpp" line="283"/>
        <location filename="../../src/MainWindow.cpp" line="344"/>
        <source>Guardant License Wizard</source>
        <translation>Asistente de licencias Guardant</translation>
    </message>
    <message>
        <location filename="../../src/MainWindow.cpp" line="158"/>
        <source>File path: </source>
        <translation>Ruta del archivo: </translation>
    </message>
    <message>
        <location filename="../../src/MainWindow.cpp" line="161"/>
        <source>Domain name: </source>
        <translation>Nombre de dominio: </translation>
    </message>
    <message>
        <location filename="../../src/MainWindow.cpp" line="164"/>
        <source>Host name: </source>
        <translation>Nombre de host: </translation>
    </message>
    <message>
        <location filename="../../src/MainWindow.cpp" line="209"/>
        <source>finished</source>
        <translation>está completo</translation>
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
        <translation>Atrás</translation>
    </message>
    <message>
        <location filename="../../src/RehostPageWidget.ui" line="155"/>
        <source>Save</source>
        <translation>Guardar</translation>
    </message>
    <message>
        <location filename="../../src/RehostPageWidget.ui" line="162"/>
        <source>After saving, the license will stop working on this computer</source>
        <translation>Después de guardar, la licencia dejará de funcionar en esta computadora</translation>
    </message>
    <message>
        <location filename="../../src/RehostPageWidget.ui" line="211"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;1. Save the &lt;span style=&quot; font-weight:600;&quot;&gt;rehost file&lt;/span&gt; to a reliable location.&lt;/p&gt;&lt;p&gt;2. Move the &lt;span style=&quot; font-weight:600;&quot;&gt;rehost file&lt;/span&gt; to the new computer and activate it with the &lt;span style=&quot; font-weight:600;&quot;&gt;Guardant License Wizard&lt;/span&gt; application.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;1. Guarde el&lt;span style=&quot; font-weight:600;&quot;&gt;archivo de transferencia&lt;/span&gt; en un lugar seguro.&lt;/p&gt;&lt;p&gt;2. Transfiera &lt;span style=&quot; font-weight:600;&quot;&gt; el archivo de transferencia&lt;/span&gt;a una computadora nueva y actívelo en la aplicación &lt;span style=&quot; font-weight:600;&quot;&gt;Asistente de licencias Guardant&lt;/span&gt;.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="../../src/RehostPageWidget.cpp" line="55"/>
        <source>License rehost </source>
        <translation>Transferencia de licencia </translation>
    </message>
</context>
<context>
    <name>RemotePageWidget</name>
    <message>
        <location filename="../../src/RemotePageWidget.ui" line="99"/>
        <source>Receive the request file on the computer where you want to use the software</source>
        <translation>Obtenga el archivo de solicitud en la computadora en la que desea utilizar el producto de software</translation>
    </message>
    <message>
        <location filename="../../src/RemotePageWidget.ui" line="139"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;1. Run the &lt;span style=&quot; font-weight:600;&quot;&gt;Guardant License Wizard&lt;/span&gt; application on it.&lt;/p&gt;&lt;p&gt;2. Push the «&lt;span style=&quot; font-weight:600;&quot;&gt;License activation&lt;/span&gt;» button → «&lt;span style=&quot; font-weight:600;&quot;&gt;Use on this computer&lt;/span&gt;» → «&lt;span style=&quot; font-weight:600;&quot;&gt;Offline activation&lt;/span&gt;».&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;1. Ejecute la aplicación en esta computadora &lt;span style=&quot; font-weight:600;&quot;&gt;Asistente de licencias Guardant&lt;/span&gt;.&lt;/p&gt;&lt;p&gt;2. Haga clic en el botón «&lt;span style=&quot; font-weight:600;&quot;&gt;Activación de la licencia&lt;/span&gt;» → «&lt;span style=&quot; font-weight:600;&quot;&gt;Usar en esta computadora&lt;/span&gt;» → «&lt;span style=&quot; font-weight:600;&quot;&gt;Activación sin conexión&lt;/span&gt;».&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="../../src/RemotePageWidget.ui" line="149"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;As a result, you will receive a &lt;span style=&quot; font-weight:600;&quot;&gt;request file&lt;/span&gt; that you need to use on this or any other computer with access to the Internet.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Como resultado, obtendrá un&lt;span style=&quot; font-weight:600;&quot;&gt; archivo de solicitud&lt;/span&gt; que debe usar en este o en cualquiera otra computadora con acceso a Internet.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="../../src/RemotePageWidget.ui" line="180"/>
        <source>Continue</source>
        <translation>Continuar</translation>
    </message>
    <message>
        <location filename="../../src/RemotePageWidget.ui" line="248"/>
        <source>License activation for another computer</source>
        <translation>Activación de la licencia para otra computadora</translation>
    </message>
    <message>
        <location filename="../../src/RemotePageWidget.ui" line="403"/>
        <source>Activate a new license</source>
        <translation>Activar licencia nueva</translation>
    </message>
    <message>
        <location filename="../../src/RemotePageWidget.ui" line="416"/>
        <source>Update this license</source>
        <translation>Actualizar esta licencia</translation>
    </message>
    <message>
        <location filename="../../src/RemotePageWidget.ui" line="429"/>
        <source>Rehost this license</source>
        <translation>Transferir esta licencia</translation>
    </message>
    <message>
        <location filename="../../src/RemotePageWidget.ui" line="516"/>
        <source>Ready</source>
        <translation>Listo</translation>
    </message>
    <message>
        <location filename="../../src/RemotePageWidget.ui" line="637"/>
        <source>Save</source>
        <translation>Guardar</translation>
    </message>
    <message>
        <location filename="../../src/RemotePageWidget.ui" line="647"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Send the received &lt;span style=&quot; font-weight:600;&quot;&gt;license file&lt;/span&gt; to the computer where you want to use the software.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Envíe el&lt;span style=&quot; font-weight:600;&quot;&gt;archivo de licencia&lt;/span&gt; a la computadora en la que desea utilizar el producto de software.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="../../src/RemotePageWidget.ui" line="657"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;1. Run the &lt;span style=&quot; font-weight:600;&quot;&gt;Guardant License Wizard&lt;/span&gt; application on the computer where you want to use the software.&lt;/p&gt;&lt;p&gt;2. Push the «&lt;span style=&quot; font-weight:600;&quot;&gt;License activation&lt;/span&gt;» button → «&lt;span style=&quot; font-weight:600;&quot;&gt;Use on this computer&lt;/span&gt;» → «&lt;span style=&quot; font-weight:600;&quot;&gt;Offline activation&lt;/span&gt;».&lt;/p&gt;&lt;p&gt;3. Select the received &lt;span style=&quot; font-weight:600;&quot;&gt;license file&lt;/span&gt;.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;1. Inicie la aplicación &lt;span style=&quot; font-weight:600;&quot;&gt;Asistente de licencias Guardant&lt;/span&gt; en la computadora en la que se va a utilizar el producto de software.&lt;/p&gt;&lt;p&gt;2. Haga clic en el botón «&lt;span style=&quot; font-weight:600;&quot;&gt;Activación de la licencia&lt;/span&gt;» → «&lt;span style=&quot; font-weight:600;&quot;&gt;Usar en esta computadora&lt;/span&gt;» → «&lt;span style=&quot; font-weight:600;&quot;&gt;Activación sin conexión&lt;/span&gt;».&lt;/p&gt;&lt;p&gt;3. Seleccione el &lt;span style=&quot; font-weight:600;&quot;&gt;archivo de licencia&lt;/span&gt;.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
</context>
<context>
    <name>SettingsPageWidget</name>
    <message>
        <location filename="../../src/SettingsPageWidget.ui" line="62"/>
        <source>Back</source>
        <translation>Atrás</translation>
    </message>
    <message>
        <location filename="../../src/SettingsPageWidget.ui" line="75"/>
        <source>Settings</source>
        <translation>Configuración</translation>
    </message>
    <message>
        <location filename="../../src/SettingsPageWidget.ui" line="165"/>
        <source>License server address</source>
        <translation>Dirección del servidor de licencias</translation>
    </message>
    <message>
        <location filename="../../src/SettingsPageWidget.ui" line="184"/>
        <source>Required for the license activation, installation and update</source>
        <translation>Necesario para la activación, instalación y actualización de licencias</translation>
    </message>
    <message>
        <location filename="../../src/SettingsPageWidget.ui" line="249"/>
        <source>Automatically check license updates on startup</source>
        <translation>Comprobar automáticamente si hay actualizaciones de licencia al iniciar</translation>
    </message>
    <message>
        <location filename="../../src/SettingsPageWidget.ui" line="350"/>
        <source>Go to log directory</source>
        <translation>Ir al registro</translation>
    </message>
</context>
<context>
    <name>WriteOncePageWidget</name>
    <message>
        <location filename="../../src/WriteOncePageWidget.ui" line="62"/>
        <source>Back</source>
        <translation>Atrás</translation>
    </message>
    <message>
        <location filename="../../src/WriteOncePageWidget.ui" line="91"/>
        <source>The old license will be erased from the key on writing</source>
        <translation>La licencia antigua se borrará al escribir una licencia nueva en la clave</translation>
    </message>
    <message>
        <location filename="../../src/WriteOncePageWidget.ui" line="189"/>
        <source>Code for the license writing</source>
        <translation>Código de registro de licencia</translation>
    </message>
    <message>
        <location filename="../../src/WriteOncePageWidget.ui" line="211"/>
        <source>File with codes</source>
        <translation>Archivo de códigos</translation>
    </message>
    <message>
        <location filename="../../src/WriteOncePageWidget.ui" line="381"/>
        <source>Write</source>
        <translation>Escribir</translation>
    </message>
    <message>
        <location filename="../../src/WriteOncePageWidget.cpp" line="140"/>
        <source>Write a license to the Guardant %1 key #%2</source>
        <translation>Registro de la licencia en la clave Guardant %1 #%2</translation>
    </message>
</context>
<context>
    <name>WriteSomePageWidget</name>
    <message>
        <location filename="../../src/WriteSomePageWidget.ui" line="62"/>
        <source>Back</source>
        <translation>Atrás</translation>
    </message>
    <message>
        <location filename="../../src/WriteSomePageWidget.ui" line="78"/>
        <source>Write a license to a key</source>
        <translation>Registro de la licencia en la clave</translation>
    </message>
    <message>
        <location filename="../../src/WriteSomePageWidget.ui" line="94"/>
        <source>The old license will be erased from the key on writing</source>
        <translation>La licencia antigua se borrará al escribir una licencia nueva en la clave</translation>
    </message>
    <message>
        <location filename="../../src/WriteSomePageWidget.ui" line="193"/>
        <source>Insert a USB key to write a license</source>
        <translation>Inserte la llave USB para escribir la licencia</translation>
    </message>
    <message>
        <location filename="../../src/WriteSomePageWidget.ui" line="212"/>
        <source>Refresh</source>
        <translation>Actualizar</translation>
    </message>
    <message>
        <location filename="../../src/WriteSomePageWidget.cpp" line="350"/>
        <source>Write</source>
        <translation>Escribir</translation>
    </message>
</context>
</TS>
