<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.1" language="ja_JP">
<context>
    <name>ActivationPageWidget</name>
    <message>
        <location filename="../../src/ActivationPageWidget.ui" line="68"/>
        <source>Back</source>
        <translation>戻る</translation>
    </message>
    <message>
        <location filename="../../src/ActivationPageWidget.ui" line="81"/>
        <source>License activation</source>
        <translation>ライセンス認証</translation>
    </message>
    <message>
        <location filename="../../src/ActivationPageWidget.ui" line="94"/>
        <source>For serial number activation a computer with access to the Internet is needed</source>
        <translation>シリアル番号を有効にするには、インターネット・アクセスを用いるPCが必要です</translation>
    </message>
    <message>
        <location filename="../../src/ActivationPageWidget.ui" line="214"/>
        <source>On which computer do you want to use the license?</source>
        <translation>ライセンス認証用のPCは何ですか？</translation>
    </message>
    <message>
        <location filename="../../src/ActivationPageWidget.ui" line="234"/>
        <source>On this</source>
        <translation>このPC</translation>
    </message>
    <message>
        <location filename="../../src/ActivationPageWidget.ui" line="259"/>
        <source>On another</source>
        <translation>別のPC</translation>
    </message>
    <message>
        <location filename="../../src/ActivationPageWidget.ui" line="284"/>
        <source>Write a license to a USB key to use it on any computer</source>
        <translation>任意のコンピュータで使用できるようにライセンスをUSBキーに書き込む</translation>
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
        <translation>使用方法：
license_wizard
グラフィックモードでは作動する
license_wizard --help
このヘルプ・メッセージを表示する
license_wizard --console &lt;オペレーション&gt; &lt;引数&gt;
コンソールモードでは作動し、指定される引数を使用して
こうしたオペレーションを行う

オペレーションとその引数
--list
ライセンスのリストを表示する
--activate &lt;シリアル_番号&gt; --host &lt;url&gt;
シリアル番号を使って認証を行う
--update &lt;ライセンス_ID&gt; --host &lt;url&gt;
指定ライセンスを更新する
--activate-request &lt;リクエスト_ファイル_パス&gt;
認証用リクエストを作成する
--update-request &lt;ライセンス_ID&gt; &lt;リクエスト_ファイル_パス&gt;
指定ライセンス更新用リクエストを作成する
--activate-response &lt;シリアル_番号&gt; &lt;リクエスト_ファイル_パス&gt;
&lt;ライセンス_ファイル_パス&gt; --host &lt;url&gt;
認証用リクエストを送信する
--update-response &lt;リクエスト_ファイル_パス&gt; &lt;ライセンス_ファイル_パス&gt; --host &lt;url&gt;
更新用リクエストを送信する
--activate-offline &lt;ライセンス_ファイル_パス&gt;
ライセンス・ファイルを使って認証を行う
--update-offline &lt;ライセンス_ファイル_パス&gt;
ライセンス・ファイルを使って更新する
--rehost-extract &lt;ライセンス_ID&gt; &lt;移動_ファイル_パス&gt;
移動するためにライセンスを抽出する
--rehost &lt;移動_ファイル_パス&gt; --host &lt;url&gt;
指定ライセンスを移動する
--rehost-request &lt;プリント_ファイル_パス&gt;
移動用リクエストを作成する
--rehost-response &lt;移動_ファイル_パス&gt; &lt;プリント_ファイル_パス&gt;
&lt;ライセンス_ファイル_パス&gt; --host &lt;url&gt;
移動用リクエストを送信する
--rehost-offline &lt;ライセンス_ファイル_パス&gt;
ライセンス・ファイルを使って移動する
--dongle-set-license &lt;dongle_ID&gt; &lt;serial_number&gt; --host &lt;url&gt;
シリアル番号を使って指定されたキーで認証を行う
--dongle-blink &lt;dongle_ID&gt;
指定されたキーでLED点滅を有効にする
</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="168"/>
        <source>License activation</source>
        <translation>ライセンス認証</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="171"/>
        <source>License update</source>
        <translation>ライセンス更新</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="173"/>
        <source>License activation request creation</source>
        <translation>ライセンス認証用リクエストの作成</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="175"/>
        <source>License update request creation</source>
        <translation>ライセンス更新用リクエストの作成</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="177"/>
        <source>License activation request sending</source>
        <translation>ライセンス認証用リクエストの送信</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="179"/>
        <source>License update request sending</source>
        <translation>ライセンス更新用リクエストの送信</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="181"/>
        <source>License rehost request creation</source>
        <translation>ライセンス移動用リクエストの作成</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="183"/>
        <source>License extraction</source>
        <translation>ライセンス抽出</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="186"/>
        <source>License rehost</source>
        <translation>ライセンス移動</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="188"/>
        <source>License rehost request sending</source>
        <translation>ライセンス移動用リクエストの送信</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="190"/>
        <source>Setting license to the key</source>
        <translation>キーのライセンス認証</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="195"/>
        <source>Unexpected operation</source>
        <translation>予期しないオペレーション</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="301"/>
        <source>Incorrect license ID format
Expected 0xNNNNNNNN, where each N is a hexadecimal digit</source>
        <translation>ライセンスIDの形式が無効です
予期する形式は、各N文字は16進数である0xNNNNNNNNです</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="306"/>
        <source>Incorrect dongle ID format
Expected 0xNNNNNNNN, where each N is a hexadecimal digit</source>
        <translation>キーIDの形式が無効です
予期する形式は、各N文字は16進数である0xNNNNNNNNです</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="311"/>
        <source>Incorrect serial number format
Expected NNNNNN-NNNNNN-NNNNNN-NNNNNN-NNNNNN, where each N is a Latin letter in upper or lower case or a digit</source>
        <translation>シリアル番号の形式が無効です
予期する形式は、各N文字はラテンアルファベットの大文字又は小文字、若しくは数字であるNNNNNN-NNNNNN-NNNNNN-NNNNNN-NNNNNNです</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="316"/>
        <source>File not found: %1</source>
        <translation>見つからなかったファイル：%1</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="319"/>
        <source>Incorrect host URL format</source>
        <translation>サーバーアドレスの形式が無効です</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="322"/>
        <source>Incorrect file path</source>
        <translation>ファイルパスが無効です</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="328"/>
        <location filename="../../src/CommandLineManager.cpp" line="337"/>
        <location filename="../../src/CommandLineManager.cpp" line="430"/>
        <source>Internal error</source>
        <translation>内部エラー</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="346"/>
        <source>%1 completed</source>
        <translation>%1が完了済み</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="408"/>
        <source>Option %1 must go first</source>
        <translation>オプション%1は、順位1番です</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="412"/>
        <source>Option %1 must go last</source>
        <translation>オプション%1は、順位最後番です</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="416"/>
        <source>Incorrect number of arguments</source>
        <translation>引数の数が無効です</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="419"/>
        <source>Option %1 has incorrect value</source>
        <translation>オプション%1に付いた値は無効なのです</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="423"/>
        <source>Parameter has incorrect value</source>
        <translation>パラメータに付いた値は無効なのです</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="426"/>
        <source>Unrecognized operation</source>
        <translation>未認識のオペレーション</translation>
    </message>
    <message>
        <location filename="../../src/CommandLineManager.cpp" line="456"/>
        <source>No licenses installed!</source>
        <translation>インストールされたライセンスはない！</translation>
    </message>
</context>
<context>
    <name>DonglePageWidget</name>
    <message>
        <location filename="../../src/DonglePageWidget.ui" line="124"/>
        <source>Code for the license writing</source>
        <translation>ライセンス記録用のコード</translation>
    </message>
    <message>
        <location filename="../../src/DonglePageWidget.ui" line="143"/>
        <source>File with codes</source>
        <translation>コードを含むファイル</translation>
    </message>
    <message>
        <location filename="../../src/DonglePageWidget.ui" line="267"/>
        <source>Continue</source>
        <translation>続く</translation>
    </message>
</context>
<context>
    <name>FilePickingWidget</name>
    <message>
        <location filename="../../src/FilePickingWidget.ui" line="44"/>
        <source>Select a file, which you received as a result of an activation, an update or a rehost from another computer.</source>
        <translation>ライセンスの認証、更新若しくは別のPCからのライセンス移動の結果として受け取ったファイルを選択する。</translation>
    </message>
    <message>
        <location filename="../../src/FilePickingWidget.ui" line="60"/>
        <source>Select a fingerprint file, which you recevied from the computer, where you want to rehost the license to.</source>
        <translation>ライセンスを移動するPCから受け取ったプリント・ファイルを選択する。</translation>
    </message>
    <message>
        <location filename="../../src/FilePickingWidget.ui" line="70"/>
        <source>Select a file with codes for writing a license to the key.</source>
        <translation>ライセンス記録用のコードのあるファイルを選択する。</translation>
    </message>
    <message>
        <location filename="../../src/FilePickingWidget.ui" line="89"/>
        <source>Select a file</source>
        <translation>ファイルを選択する</translation>
    </message>
    <message>
        <location filename="../../src/FilePickingWidget.ui" line="202"/>
        <source>Incorrect file</source>
        <translation>ファイルは無効なのです</translation>
    </message>
    <message>
        <location filename="../../src/FilePickingWidget.ui" line="222"/>
        <source>Select another one</source>
        <translation>他のファイルを選択する</translation>
    </message>
    <message>
        <location filename="../../src/FilePickingWidget.cpp" line="233"/>
        <source>There are %1 codes (keys) in this file</source>
        <translation>ファイルはコード (キー) の%1を含む</translation>
    </message>
</context>
<context>
    <name>LicenseItemWidget</name>
    <message>
        <location filename="../../src/LicenseItemWidget.ui" line="82"/>
        <source>Trial Software Key</source>
        <translation>トライアルソフトウェアキー</translation>
    </message>
    <message>
        <location filename="../../src/LicenseItemWidget.ui" line="110"/>
        <source>Vendor code</source>
        <translation>アクセスコード</translation>
    </message>
    <message>
        <location filename="../../src/LicenseItemWidget.ui" line="197"/>
        <source>Update license</source>
        <translation>更新をインストールする</translation>
    </message>
    <message>
        <location filename="../../src/LicenseItemWidget.ui" line="239"/>
        <source>Check updates</source>
        <translation>更新を確認する</translation>
    </message>
    <message>
        <location filename="../../src/LicenseItemWidget.ui" line="244"/>
        <source>Offline update</source>
        <translation>オフライン更新</translation>
    </message>
    <message>
        <location filename="../../src/LicenseItemWidget.ui" line="249"/>
        <source>Move to another computer</source>
        <translation>別のPCに移動する</translation>
    </message>
    <message>
        <location filename="../../src/LicenseItemWidget.ui" line="254"/>
        <source>Remove</source>
        <translation>削除</translation>
    </message>
    <message>
        <location filename="../../src/LicenseItemWidget.ui" line="259"/>
        <source>Write a license to this key</source>
        <translation>このキーにライセンスを書き込む</translation>
    </message>
</context>
<context>
    <name>LicensePickingWidget</name>
    <message>
        <location filename="../../src/LicensePickingWidget.ui" line="44"/>
        <source>Select the license</source>
        <translation>ライセンスを選択する</translation>
    </message>
    <message>
        <location filename="../../src/LicensePickingWidget.ui" line="176"/>
        <source>No licenses installed</source>
        <translation>インストールされたライセンスはない</translation>
    </message>
    <message>
        <location filename="../../src/LicensePickingWidget.cpp" line="309"/>
        <source>Select</source>
        <translation>選択する</translation>
    </message>
</context>
<context>
    <name>ListPageWidget</name>
    <message>
        <location filename="../../src/ListPageWidget.ui" line="71"/>
        <source>Licenses</source>
        <translation>ライセンス</translation>
    </message>
    <message>
        <location filename="../../src/ListPageWidget.ui" line="91"/>
        <source>License activation</source>
        <translation>ライセンス認証</translation>
    </message>
    <message>
        <location filename="../../src/ListPageWidget.ui" line="135"/>
        <source>No license found on this computer</source>
        <translation>このPCには、いかなるライセンスが見つからなかった</translation>
    </message>
    <message>
        <location filename="../../src/ListPageWidget.ui" line="178"/>
        <source>What do you have?</source>
        <translation>何があるんだ？</translation>
    </message>
    <message>
        <location filename="../../src/ListPageWidget.ui" line="207"/>
        <source>Serial number, license file</source>
        <translation>シリアル番号、ライセンス・ファイル</translation>
    </message>
    <message>
        <location filename="../../src/ListPageWidget.ui" line="220"/>
        <source>Activate a license</source>
        <translation>ライセンス認証を行う</translation>
    </message>
    <message>
        <location filename="../../src/ListPageWidget.ui" line="233"/>
        <source>USB key</source>
        <translation>USBキー</translation>
    </message>
    <message>
        <location filename="../../src/ListPageWidget.ui" line="246"/>
        <source>Insert it in this computer</source>
        <translation>このPCに挿入する</translation>
    </message>
    <message>
        <location filename="../../src/ListPageWidget.ui" line="292"/>
        <source>Licensing
terms</source>
        <translation>ライセンス
制限</translation>
    </message>
    <message>
        <location filename="../../src/ListPageWidget.ui" line="298"/>
        <source>Concurrent
instances</source>
        <translation>ネットワーク
リソース</translation>
    </message>
    <message>
        <location filename="../../src/ListPageWidget.ui" line="304"/>
        <source>VM
enabled</source>
        <translation>VM上で
作業中</translation>
    </message>
    <message>
        <location filename="../../src/ListPageWidget.cpp" line="587"/>
        <source>The number of machines on which the Feature is running simultaneously</source>
        <translation>コンポーネントが同時に実行されている台数</translation>
    </message>
    <message>
        <location filename="../../src/ListPageWidget.cpp" line="590"/>
        <source>The number of API connections</source>
        <translation>API接続数</translation>
    </message>
    <message>
        <location filename="../../src/ListPageWidget.cpp" line="592"/>
        <source>The number of running instances of the Feature</source>
        <translation>起動したコンポーネントのインスタンス数</translation>
    </message>
</context>
<context>
    <name>MainPageWidget</name>
    <message>
        <location filename="../../src/MainPageWidget.ui" line="83"/>
        <source>Settings</source>
        <translation>設定</translation>
    </message>
    <message>
        <location filename="../../src/MainPageWidget.cpp" line="286"/>
        <location filename="../../src/MainPageWidget.cpp" line="310"/>
        <source>Internal error</source>
        <translation>内部エラー</translation>
    </message>
    <message>
        <location filename="../../src/MainPageWidget.cpp" line="288"/>
        <source>License installed</source>
        <translation>ライセンスがインストールされた</translation>
    </message>
    <message>
        <location filename="../../src/MainPageWidget.cpp" line="290"/>
        <source>License updated</source>
        <translation>ライセンスが更新された</translation>
    </message>
    <message>
        <location filename="../../src/MainPageWidget.cpp" line="292"/>
        <source>License update available</source>
        <translation>ライセンスの更新がある</translation>
    </message>
    <message>
        <location filename="../../src/MainPageWidget.cpp" line="294"/>
        <source>Licenses updates available</source>
        <translation>ライセンスの更新がある</translation>
    </message>
    <message>
        <location filename="../../src/MainPageWidget.cpp" line="296"/>
        <source>No more license updates</source>
        <translation>ライセンスの更新がない</translation>
    </message>
    <message>
        <location filename="../../src/MainPageWidget.cpp" line="298"/>
        <source>Unable to check license updates</source>
        <translation>更新を確認できない</translation>
    </message>
    <message>
        <location filename="../../src/MainPageWidget.cpp" line="300"/>
        <source>Unable to check licenses updates</source>
        <translation>更新を確認できない</translation>
    </message>
    <message>
        <location filename="../../src/MainPageWidget.cpp" line="302"/>
        <source>Unable to update the license</source>
        <translation>ライセンスを更新できない</translation>
    </message>
    <message>
        <location filename="../../src/MainPageWidget.cpp" line="304"/>
        <source>License extracted</source>
        <translation>ライセンスは抽出された</translation>
    </message>
    <message>
        <location filename="../../src/MainPageWidget.cpp" line="314"/>
        <source>License ID copied to clipboard</source>
        <translation>ライセンスIDがクリップボードにコピーされました</translation>
    </message>
</context>
<context>
    <name>MainWindow</name>
    <message>
        <location filename="../../src/MainWindow.cpp" line="345"/>
        <source>Entered data is not URL</source>
        <translation>入力されたデータはURLではない</translation>
    </message>
</context>
<context>
    <name>OfflinePageWidget</name>
    <message>
        <location filename="../../src/OfflinePageWidget.ui" line="84"/>
        <source>Offline activation</source>
        <translation>オフライン認証</translation>
    </message>
    <message>
        <location filename="../../src/OfflinePageWidget.ui" line="177"/>
        <source>New license</source>
        <translation>新たなライセンス</translation>
    </message>
    <message>
        <location filename="../../src/OfflinePageWidget.ui" line="196"/>
        <source>License update</source>
        <translation>ライセンス更新</translation>
    </message>
    <message>
        <location filename="../../src/OfflinePageWidget.ui" line="215"/>
        <source>License rehost</source>
        <translation>ライセンス移動</translation>
    </message>
    <message>
        <location filename="../../src/OfflinePageWidget.ui" line="274"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Save the &lt;span style=&quot; font-weight:600;&quot;&gt;fingerprint file&lt;/span&gt;. It contains info for license rehost with the help of another computer with access to the Internet.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;プリント・ファイル&lt;span style=&quot; font-weight:600;&quot;&gt;を保存する&lt;/span&gt;.別のインターネット・アクセスを用いるPCでライセンスの移動に必要な情報を含む。&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="../../src/OfflinePageWidget.ui" line="284"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Save the &lt;span style=&quot; font-weight:600;&quot;&gt;request file&lt;/span&gt;. It contains info for license activation on another computer with access to the Internet.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;リクエスト・ファイル&lt;span style=&quot; font-weight:600;&quot;&gt;を保存する&lt;/span&gt;.。別のインターネット・アクセスを用いるPCでライセンスの認証に必要な情報を含む。&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="../../src/OfflinePageWidget.ui" line="381"/>
        <source>Save</source>
        <translation>保存する</translation>
    </message>
    <message>
        <location filename="../../src/OfflinePageWidget.ui" line="412"/>
        <source>Continue</source>
        <translation>続く</translation>
    </message>
    <message>
        <location filename="../../src/OfflinePageWidget.ui" line="473"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;1. Move the saved &lt;span style=&quot; font-weight:600;&quot;&gt;request file&lt;/span&gt; and &lt;span style=&quot; font-weight:600;&quot;&gt;serial number&lt;/span&gt; to the computer with access to the Internet.&lt;/p&gt;&lt;p&gt;2. Run the &lt;span style=&quot; font-weight:600;&quot;&gt;Guardant License Wizard&lt;/span&gt; application on it.&lt;/p&gt;&lt;p&gt;3. Push the «&lt;span style=&quot; font-weight:600;&quot;&gt;License activation&lt;/span&gt;» button and activate a license for another computer.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;1.保存した&lt;span style=&quot; font-weight:600;&quot;&gt;リクエスト・ファイル&lt;/span&gt; と &lt;span style=&quot; font-weight:600;&quot;&gt;シリアル番号&lt;/span&gt; を、インターネット・アクセスを用いるPCに移動する。&lt;/p&gt;&lt;p&gt;2.&lt;span style=&quot; font-weight:600;&quot;&gt;Guardantライセンス・ウィザード&lt;/span&gt;というアプリを起動する。&lt;/p&gt;&lt;p&gt;3.«&lt;span style=&quot; font-weight:600;&quot;&gt;ライセンス認証&lt;/span&gt;» をクリックして別のPCでライセンスの認証を行う。&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="../../src/OfflinePageWidget.ui" line="483"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;1. Move the saved &lt;span style=&quot; font-weight:600;&quot;&gt;request file&lt;/span&gt; to the computer with access to the Internet.&lt;/p&gt;&lt;p&gt;2. Run the &lt;span style=&quot; font-weight:600;&quot;&gt;Guardant License Wizard&lt;/span&gt; application on it.&lt;/p&gt;&lt;p&gt;3. Push the «&lt;span style=&quot; font-weight:600;&quot;&gt;License activation&lt;/span&gt;» button and update a license for another computer.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;1.保存した &lt;span style=&quot; font-weight:600;&quot;&gt;リクエスト・ファイル&lt;/span&gt; を、インターネット・アクセスを用いるPCに移動する。&lt;/p&gt;&lt;p&gt;2.&lt;span style=&quot; font-weight:600;&quot;&gt;Guardantライセンス・ウィザード&lt;/span&gt;というアプリを起動する。&lt;/p&gt;&lt;p&gt;3.«&lt;span style=&quot; font-weight:600;&quot;&gt;ライセンス認証&lt;/span&gt;»をクリックして別のPCでライセンスを更新する。&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="../../src/OfflinePageWidget.ui" line="493"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;1. Move the &lt;span style=&quot; font-weight:600;&quot;&gt;rehost file&lt;/span&gt;, recevied from the other computer, and the saved &lt;span style=&quot; font-weight:600;&quot;&gt;fingerprint file&lt;/span&gt;, to the computer with access to the Internet.&lt;/p&gt;&lt;p&gt;2. Run the &lt;span style=&quot; font-weight:600;&quot;&gt;Guardant License Wizard&lt;/span&gt; application on it.&lt;/p&gt;&lt;p&gt;3. Push the «&lt;span style=&quot; font-weight:600;&quot;&gt;License activation&lt;/span&gt;» button and activate a license for another computer.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;1.&lt;span style=&quot; font-weight:600;&quot;&gt;別のPCから取得した移動ファイル&lt;/span&gt;, と保存した&lt;span style=&quot; font-weight:600;&quot;&gt;プリント・ファイル&lt;/span&gt; を、インターネット・アクセスを用いるPCに移動する。&lt;/p&gt;&lt;p&gt;2.&lt;span style=&quot; font-weight:600;&quot;&gt;Guardantライセンス・ウィザード&lt;/span&gt;というアプリを起動する。&lt;/p&gt;&lt;p&gt;3. «&lt;span style=&quot; font-weight:600;&quot;&gt;ライセンス認証&lt;/span&gt;»をクリックしてライセンスを別のPCに転送する。&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="../../src/OfflinePageWidget.ui" line="506"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;As a result, you will receive a new &lt;span style=&quot; font-weight:600;&quot;&gt;license file&lt;/span&gt; that you need to activate on this computer.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;その結果、このPCで認証するべき新たな &lt;span style=&quot; font-weight:600;&quot;&gt;ライセンス・ファイル&lt;/span&gt;を受け取ることになる。&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="../../src/OfflinePageWidget.ui" line="537"/>
        <source>Continue, I have the license file</source>
        <translation>ライセンス・ファイルがあるため、続く</translation>
    </message>
    <message>
        <location filename="../../src/OfflinePageWidget.ui" line="590"/>
        <source>Activate with license file</source>
        <translation>ライセンス・ファイルを使って認証を行うこと</translation>
    </message>
</context>
<context>
    <name>OnlinePageWidget</name>
    <message>
        <location filename="../../src/OnlinePageWidget.ui" line="121"/>
        <source>Serial number</source>
        <translation>シリアル番号</translation>
    </message>
    <message>
        <location filename="../../src/OnlinePageWidget.ui" line="140"/>
        <source>License file or rehost file</source>
        <translation>ライセンス・ファイル又は移動ファイル</translation>
    </message>
    <message>
        <location filename="../../src/OnlinePageWidget.ui" line="172"/>
        <source>Offline activation</source>
        <translation>オフライン認証</translation>
    </message>
    <message>
        <location filename="../../src/OnlinePageWidget.ui" line="277"/>
        <source>Get license</source>
        <translation>ライセンスを受け取る</translation>
    </message>
</context>
<context>
    <name>QLineEdit</name>
    <message>
        <location filename="../../src/MainWindow.cpp" line="55"/>
        <source>&amp;Undo</source>
        <translation>元に戻す</translation>
    </message>
    <message>
        <location filename="../../src/MainWindow.cpp" line="56"/>
        <source>&amp;Redo</source>
        <translation>やり直す</translation>
    </message>
    <message>
        <location filename="../../src/MainWindow.cpp" line="57"/>
        <source>Cu&amp;t</source>
        <translation>切り取り</translation>
    </message>
    <message>
        <location filename="../../src/MainWindow.cpp" line="58"/>
        <source>&amp;Copy</source>
        <translation>コピー</translation>
    </message>
    <message>
        <location filename="../../src/MainWindow.cpp" line="59"/>
        <source>&amp;Paste</source>
        <translation>貼り付け</translation>
    </message>
    <message>
        <location filename="../../src/MainWindow.cpp" line="60"/>
        <source>Delete</source>
        <translation>削除</translation>
    </message>
    <message>
        <location filename="../../src/MainWindow.cpp" line="61"/>
        <source>Select All</source>
        <translation>すべてを選択</translation>
    </message>
</context>
<context>
    <name>QObject</name>
    <message>
        <location filename="../../src/Common.h" line="29"/>
        <source>Request file</source>
        <translation>リクエスト・ファイル</translation>
    </message>
    <message>
        <location filename="../../src/Common.h" line="31"/>
        <source>License file</source>
        <translation>ライセンス・ファイル</translation>
    </message>
    <message>
        <location filename="../../src/Common.h" line="33"/>
        <source>Rehost file</source>
        <translation>移動ファイル</translation>
    </message>
    <message>
        <location filename="../../src/Common.h" line="35"/>
        <source>Fingerprint file</source>
        <translation>プリント・ファイル</translation>
    </message>
    <message>
        <location filename="../../src/Common.h" line="46"/>
        <source>Request files</source>
        <translation>リクエスト・ファイル</translation>
    </message>
    <message>
        <location filename="../../src/Common.h" line="49"/>
        <source>License files</source>
        <translation>ライセンス・ファイル</translation>
    </message>
    <message>
        <location filename="../../src/Common.h" line="52"/>
        <source>Rehost files</source>
        <translation>移動ファイル</translation>
    </message>
    <message>
        <location filename="../../src/Common.h" line="55"/>
        <source>Fingerprint files</source>
        <translation>プリント・ファイル</translation>
    </message>
    <message>
        <location filename="../../src/Common.h" line="66"/>
        <source>License and rehost files</source>
        <translation>ライセンス・ファイルや移動ファイル</translation>
    </message>
    <message>
        <location filename="../../src/Common.h" line="70"/>
        <source>Request and rehost files</source>
        <translation>リクエスト・ファイルや移動ファイル</translation>
    </message>
    <message>
        <location filename="../../src/Common.h" line="77"/>
        <source>All files</source>
        <translation>全てのファイル</translation>
    </message>
    <message>
        <location filename="../../src/Feature.h" line="29"/>
        <source>Number of launches: </source>
        <translation>起動数：</translation>
    </message>
    <message>
        <location filename="../../src/Feature.h" line="33"/>
        <source>Number of days: </source>
        <translation>日数：</translation>
    </message>
    <message>
        <location filename="../../src/Feature.h" line="36"/>
        <source>No restrictions</source>
        <translation>制限なし</translation>
    </message>
    <message>
        <location filename="../../src/Feature.h" line="88"/>
        <source>Work station</source>
        <translation>ワークステーション</translation>
    </message>
    <message>
        <location filename="../../src/Feature.h" line="91"/>
        <source>Connection</source>
        <translation>接続</translation>
    </message>
    <message>
        <location filename="../../src/Feature.h" line="94"/>
        <source>Program copy</source>
        <translation>プログラムのコピー</translation>
    </message>
    <message>
        <location filename="../../src/GrdLicApi.h" line="51"/>
        <source>NO DESCRIPTION</source>
        <translation>説明なし</translation>
    </message>
    <message>
        <location filename="../../src/GrdLicApi.h" line="55"/>
        <source>serial number</source>
        <translation>シリアル番号</translation>
    </message>
    <message>
        <location filename="../../src/GrdLicApi.h" line="58"/>
        <source>license ID</source>
        <translation>ライセンスID</translation>
    </message>
    <message>
        <location filename="../../src/GrdLicApi.h" line="63"/>
        <source>address</source>
        <translation>アドレス</translation>
    </message>
    <message>
        <location filename="../../src/GrdLicApi.h" line="65"/>
        <source>port</source>
        <translation>ポート</translation>
    </message>
    <message>
        <location filename="../../src/GrdLicApi.h" line="72"/>
        <source>status code</source>
        <translation>状態コード</translation>
    </message>
    <message>
        <location filename="../../src/GrdLicApi.h" line="74"/>
        <source>message</source>
        <translation>メッセージ</translation>
    </message>
    <message>
        <location filename="../../src/License.h" line="230"/>
        <source>Key</source>
        <translation>キー</translation>
    </message>
    <message>
        <location filename="../../src/License.h" line="231"/>
        <source>License</source>
        <translation>ライセンス</translation>
    </message>
    <message>
        <location filename="../../src/MainWindow.cpp" line="149"/>
        <location filename="../../src/MainWindow.cpp" line="208"/>
        <location filename="../../src/MainWindow.cpp" line="283"/>
        <location filename="../../src/MainWindow.cpp" line="344"/>
        <source>Guardant License Wizard</source>
        <translation>Guardantライセンス・ウィザード</translation>
    </message>
    <message>
        <location filename="../../src/MainWindow.cpp" line="158"/>
        <source>File path: </source>
        <translation>ファイルパス: </translation>
    </message>
    <message>
        <location filename="../../src/MainWindow.cpp" line="161"/>
        <source>Domain name: </source>
        <translation>ドメイン名: </translation>
    </message>
    <message>
        <location filename="../../src/MainWindow.cpp" line="164"/>
        <source>Host name: </source>
        <translation>ホスト名: </translation>
    </message>
    <message>
        <location filename="../../src/MainWindow.cpp" line="209"/>
        <source>finished</source>
        <translation>完了した</translation>
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
        <translation>戻る</translation>
    </message>
    <message>
        <location filename="../../src/RehostPageWidget.ui" line="155"/>
        <source>Save</source>
        <translation>保存する</translation>
    </message>
    <message>
        <location filename="../../src/RehostPageWidget.ui" line="162"/>
        <source>After saving, the license will stop working on this computer</source>
        <translation>一度保存されたライセンスは、このPCでは機能できなくなる</translation>
    </message>
    <message>
        <location filename="../../src/RehostPageWidget.ui" line="211"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;1. Save the &lt;span style=&quot; font-weight:600;&quot;&gt;rehost file&lt;/span&gt; to a reliable location.&lt;/p&gt;&lt;p&gt;2. Move the &lt;span style=&quot; font-weight:600;&quot;&gt;rehost file&lt;/span&gt; to the new computer and activate it with the &lt;span style=&quot; font-weight:600;&quot;&gt;Guardant License Wizard&lt;/span&gt; application.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;1.&lt;span style=&quot; font-weight:600;&quot;&gt;移動ファイル&lt;/span&gt;を安全な場所に保存する。&lt;/p&gt;&lt;p&gt;2.&lt;span style=&quot; font-weight:600;&quot;&gt;移行ファイルを&lt;/span&gt;を新たなPCに転送し、 &lt;span style=&quot; font-weight:600;&quot;&gt;Guardantライセンス・ウィザード&lt;/span&gt;というアプリで認証する。&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="../../src/RehostPageWidget.cpp" line="55"/>
        <source>License rehost </source>
        <translation>ライセンス移動</translation>
    </message>
</context>
<context>
    <name>RemotePageWidget</name>
    <message>
        <location filename="../../src/RemotePageWidget.ui" line="99"/>
        <source>Receive the request file on the computer where you want to use the software</source>
        <translation>ソフトウェア製品を使用したいPCでリクエスト・ファイルを取得する</translation>
    </message>
    <message>
        <location filename="../../src/RemotePageWidget.ui" line="139"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;1. Run the &lt;span style=&quot; font-weight:600;&quot;&gt;Guardant License Wizard&lt;/span&gt; application on it.&lt;/p&gt;&lt;p&gt;2. Push the «&lt;span style=&quot; font-weight:600;&quot;&gt;License activation&lt;/span&gt;» button → «&lt;span style=&quot; font-weight:600;&quot;&gt;Use on this computer&lt;/span&gt;» → «&lt;span style=&quot; font-weight:600;&quot;&gt;Offline activation&lt;/span&gt;».&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;1.&lt;span style=&quot; font-weight:600;&quot;&gt;Guardantライセンス・ウィザード&lt;/span&gt;というアプリを起動する。&lt;/p&gt;&lt;p&gt;2.«&lt;span style=&quot; font-weight:600;&quot;&gt;ライセンス認証&lt;/span&gt;»をクリックして → «&lt;span style=&quot; font-weight:600;&quot;&gt;このPCで使用する&lt;/span&gt;» → «&lt;span style=&quot; font-weight:600;&quot;&gt;オフライン認証&lt;/span&gt;»をクリックする。&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="../../src/RemotePageWidget.ui" line="149"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;As a result, you will receive a &lt;span style=&quot; font-weight:600;&quot;&gt;request file&lt;/span&gt; that you need to use on this or any other computer with access to the Internet.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;これにより、&lt;span style=&quot; font-weight:600;&quot;&gt;このコンピューター又はあらゆるインターネット・アクセスを用いるPCで使用するべき&lt;/span&gt;リクエストファイルを取得する。&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="../../src/RemotePageWidget.ui" line="180"/>
        <source>Continue</source>
        <translation>続く</translation>
    </message>
    <message>
        <location filename="../../src/RemotePageWidget.ui" line="248"/>
        <source>License activation for another computer</source>
        <translation>別のPCに対するライセンス認証</translation>
    </message>
    <message>
        <location filename="../../src/RemotePageWidget.ui" line="403"/>
        <source>Activate a new license</source>
        <translation>新たなライセンス認証を行う</translation>
    </message>
    <message>
        <location filename="../../src/RemotePageWidget.ui" line="416"/>
        <source>Update this license</source>
        <translation>ライセンスを更新する</translation>
    </message>
    <message>
        <location filename="../../src/RemotePageWidget.ui" line="429"/>
        <source>Rehost this license</source>
        <translation>ライセンスを移動する</translation>
    </message>
    <message>
        <location filename="../../src/RemotePageWidget.ui" line="516"/>
        <source>Ready</source>
        <translation>完了</translation>
    </message>
    <message>
        <location filename="../../src/RemotePageWidget.ui" line="637"/>
        <source>Save</source>
        <translation>保存する</translation>
    </message>
    <message>
        <location filename="../../src/RemotePageWidget.ui" line="647"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Send the received &lt;span style=&quot; font-weight:600;&quot;&gt;license file&lt;/span&gt; to the computer where you want to use the software.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;取得した &lt;span style=&quot; font-weight:600;&quot;&gt;ライセンス・ファイル&lt;/span&gt;をソフトウェア製品を使用したいPCに移動する。&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="../../src/RemotePageWidget.ui" line="657"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;1. Run the &lt;span style=&quot; font-weight:600;&quot;&gt;Guardant License Wizard&lt;/span&gt; application on the computer where you want to use the software.&lt;/p&gt;&lt;p&gt;2. Push the «&lt;span style=&quot; font-weight:600;&quot;&gt;License activation&lt;/span&gt;» button → «&lt;span style=&quot; font-weight:600;&quot;&gt;Use on this computer&lt;/span&gt;» → «&lt;span style=&quot; font-weight:600;&quot;&gt;Offline activation&lt;/span&gt;».&lt;/p&gt;&lt;p&gt;3. Select the received &lt;span style=&quot; font-weight:600;&quot;&gt;license file&lt;/span&gt;.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;1.ソフトウェア製品を使用するPCに&lt;span style=&quot; font-weight:600;&quot;&gt;Guardantライセンス・ウィザード&lt;/span&gt; というアプリを起動する。&lt;/p&gt;&lt;p&gt;2. «&lt;span style=&quot; font-weight:600;&quot;&gt;ライセンス認証&lt;/span&gt;»をクリックして→ «&lt;span style=&quot; font-weight:600;&quot;&gt;このPCで使用する&lt;/span&gt;» → «&lt;span style=&quot; font-weight:600;&quot;&gt;オフライン認証&lt;/span&gt;»をクリックする。&lt;/p&gt;&lt;p&gt;3.取得した &lt;span style=&quot; font-weight:600;&quot;&gt;ライセンス・ファイル&lt;/span&gt;を選択する。&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
</context>
<context>
    <name>SettingsPageWidget</name>
    <message>
        <location filename="../../src/SettingsPageWidget.ui" line="62"/>
        <source>Back</source>
        <translation>戻る</translation>
    </message>
    <message>
        <location filename="../../src/SettingsPageWidget.ui" line="75"/>
        <source>Settings</source>
        <translation>設定</translation>
    </message>
    <message>
        <location filename="../../src/SettingsPageWidget.ui" line="165"/>
        <source>License server address</source>
        <translation>ライセンスサーバアドレス</translation>
    </message>
    <message>
        <location filename="../../src/SettingsPageWidget.ui" line="184"/>
        <source>Required for the license activation, installation and update</source>
        <translation>ライセンスのアクティベーション、インストール、更新に必要</translation>
    </message>
    <message>
        <location filename="../../src/SettingsPageWidget.ui" line="249"/>
        <source>Automatically check license updates on startup</source>
        <translation>起動時にライセンスの更新を自動的に確認する</translation>
    </message>
    <message>
        <location filename="../../src/SettingsPageWidget.ui" line="350"/>
        <source>Go to log directory</source>
        <translation>ジャーナルへ行く</translation>
    </message>
</context>
<context>
    <name>WriteOncePageWidget</name>
    <message>
        <location filename="../../src/WriteOncePageWidget.ui" line="62"/>
        <source>Back</source>
        <translation>戻る</translation>
    </message>
    <message>
        <location filename="../../src/WriteOncePageWidget.ui" line="91"/>
        <source>The old license will be erased from the key on writing</source>
        <translation>新たなライセンスがキーに記録されると、古いライセンスは消去される</translation>
    </message>
    <message>
        <location filename="../../src/WriteOncePageWidget.ui" line="189"/>
        <source>Code for the license writing</source>
        <translation>ライセンス記録用のコード</translation>
    </message>
    <message>
        <location filename="../../src/WriteOncePageWidget.ui" line="211"/>
        <source>File with codes</source>
        <translation>コードを含むファイル</translation>
    </message>
    <message>
        <location filename="../../src/WriteOncePageWidget.ui" line="381"/>
        <source>Write</source>
        <translation>記録する</translation>
    </message>
    <message>
        <location filename="../../src/WriteOncePageWidget.cpp" line="140"/>
        <source>Write a license to the Guardant %1 key #%2</source>
        <translation>Guardant %1 #%2キーにライセンスを記録する</translation>
    </message>
</context>
<context>
    <name>WriteSomePageWidget</name>
    <message>
        <location filename="../../src/WriteSomePageWidget.ui" line="62"/>
        <source>Back</source>
        <translation>戻る</translation>
    </message>
    <message>
        <location filename="../../src/WriteSomePageWidget.ui" line="78"/>
        <source>Write a license to a key</source>
        <translation>キーにライセンスを記録する</translation>
    </message>
    <message>
        <location filename="../../src/WriteSomePageWidget.ui" line="94"/>
        <source>The old license will be erased from the key on writing</source>
        <translation>新たなライセンスがキーに記録されると、古いライセンスは消去される</translation>
    </message>
    <message>
        <location filename="../../src/WriteSomePageWidget.ui" line="193"/>
        <source>Insert a USB key to write a license</source>
        <translation>ライセンスを記録するには、USBキーを挿入する</translation>
    </message>
    <message>
        <location filename="../../src/WriteSomePageWidget.ui" line="212"/>
        <source>Refresh</source>
        <translation>更新する</translation>
    </message>
    <message>
        <location filename="../../src/WriteSomePageWidget.cpp" line="350"/>
        <source>Write</source>
        <translation>記録する</translation>
    </message>
</context>
</TS>
