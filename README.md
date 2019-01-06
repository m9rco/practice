<p>
    <span style="font-size: 16px; font-family: SimSun, STSong; color: rgb(102, 102, 102); background-color: rgb(255, 255, 255);">Linux服务器mail程序本身就是调用sendmail来进行邮件发送的，sendmail服务器提供对外的邮件发送功能。CentOS默认不能发送邮件，需要发送邮件的童鞋可以安装一个sendmail程序</span>
</p>
<table width="0">
    <colgroup>
        <col style="width: 70px;"/>
        <col style="width: 1194px;"/>
    </colgroup>
    <tbody>
        <tr style="height: 40px;" class="firstRow">
            <td style="font-size: 14px; color: rgb(57, 57, 57); border-color: rgb(167, 167, 167); overflow: hidden; overflow-wrap: break-word; white-space: pre-wrap;">
                <p>
                    <span style="font-family: &quot;Courier New&quot;; color: rgb(0, 0, 0); background-color: rgb(255, 255, 255);">1</span>
                </p>
                <p>
                    <span style="font-family: &quot;Courier New&quot;; color: rgb(0, 0, 0); background-color: rgb(255, 255, 255);">2</span>
                </p>
                <p>
                    <span style="font-family: &quot;Courier New&quot;; color: rgb(0, 0, 0); background-color: rgb(255, 255, 255);">3</span>
                </p>
                <p>
                    <span style="font-family: &quot;Courier New&quot;; color: rgb(0, 0, 0); background-color: rgb(255, 255, 255);">4</span>
                </p>
                <p>
                    <span style="font-family: &quot;Courier New&quot;; color: rgb(0, 0, 0); background-color: rgb(255, 255, 255);">5</span>
                </p>
                <p>
                    <span style="font-family: &quot;Courier New&quot;; color: rgb(0, 0, 0); background-color: rgb(255, 255, 255);">6</span>
                </p>
                <p>
                    <span style="font-family: &quot;Courier New&quot;; color: rgb(0, 0, 0); background-color: rgb(255, 255, 255);">7</span>
                </p>
                <p>
                    <span style="font-family: &quot;Courier New&quot;; color: rgb(0, 0, 0); background-color: rgb(255, 255, 255);">8</span>
                </p>
                <p>
                    <span style="font-family: &quot;Courier New&quot;; color: rgb(0, 0, 0); background-color: rgb(255, 255, 255);">9</span>
                </p>
                <p>
                    <span style="font-family: &quot;Courier New&quot;; color: rgb(0, 0, 0); background-color: rgb(255, 255, 255);">10</span>
                </p>
                <p>
                    <span style="font-family: &quot;Courier New&quot;; color: rgb(0, 0, 0); background-color: rgb(255, 255, 255);">11</span>
                </p>
                <p>
                    <span style="font-family: &quot;Courier New&quot;; color: rgb(0, 0, 0); background-color: rgb(255, 255, 255);">12</span>
                </p>
            </td>
            <td style="font-size: 14px; color: rgb(57, 57, 57); border-color: rgb(167, 167, 167); overflow: hidden; overflow-wrap: break-word; white-space: pre-wrap;">
                <p>
                    <span style="font-family: &quot;Courier New&quot;; color: rgb(0, 0, 0); background-color: rgb(255, 255, 255);">[root@ProxyServer&nbsp;~]</span><span style="font-family: &quot;Courier New&quot;; color: rgb(0, 130, 0); background-color: rgb(255, 255, 255);">#&nbsp;yum&nbsp;-y&nbsp;install&nbsp;sendmail</span>
                </p>
                <p>
                    <span style="font-family: &quot;Courier New&quot;; color: rgb(0, 0, 0); background-color: rgb(255, 255, 255);">[root@ProxyServer&nbsp;~]</span><span style="font-family: &quot;Courier New&quot;; color: rgb(0, 130, 0); background-color: rgb(255, 255, 255);">#&nbsp;/etc/init.d/sendmail&nbsp;start</span>
                </p>
                <p>
                    <span style="font-family: &quot;Courier New&quot;; color: rgb(0, 0, 0); background-color: rgb(255, 255, 255);">Starting&nbsp;sendmail:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[&nbsp;&nbsp;OK&nbsp;&nbsp;]</span>
                </p>
                <p>
                    <span style="font-family: &quot;Courier New&quot;; color: rgb(0, 0, 0); background-color: rgb(255, 255, 255);">Starting&nbsp;sm-client:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[&nbsp;&nbsp;OK&nbsp;&nbsp;]</span>
                </p>
                <p>
                    <span style="font-family: &quot;Courier New&quot;; color: rgb(0, 0, 0); background-color: rgb(255, 255, 255);">[root@ProxyServer&nbsp;~]</span><span style="font-family: &quot;Courier New&quot;; color: rgb(0, 130, 0); background-color: rgb(255, 255, 255);">#&nbsp;chkconfig&nbsp;sendmail&nbsp;on</span>
                </p>
                <p>
                    <span style="font-family: &quot;Courier New&quot;; color: rgb(0, 0, 0); background-color: rgb(255, 255, 255);">[root@ProxyServer&nbsp;~]</span><span style="font-family: &quot;Courier New&quot;; color: rgb(0, 130, 0); background-color: rgb(255, 255, 255);">#&nbsp;man&nbsp;mail</span>
                </p>
                <p>
                    <span style="font-family: &quot;Courier New&quot;; color: rgb(0, 0, 0); background-color: rgb(255, 255, 255);">......</span>
                </p>
                <p>
                    <span style="font-family: &quot;Courier New&quot;; color: rgb(0, 0, 0); background-color: rgb(255, 255, 255);">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mailx&nbsp;[-BDdEFintv~]&nbsp;[-s&nbsp;subject]&nbsp;[-a&nbsp;attachment&nbsp;]&nbsp;[-c&nbsp;cc-addr]&nbsp;[-b&nbsp;bcc-addr]&nbsp;[-r&nbsp;from-addr]&nbsp;[-h&nbsp;hops]&nbsp;[-A&nbsp;account]</span>
                </p>
                <p>
                    <span style="font-family: &quot;Courier New&quot;; color: rgb(0, 0, 0); background-color: rgb(255, 255, 255);">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[-S&nbsp;variable[=value]]&nbsp;to-addr&nbsp;.&nbsp;.&nbsp;.</span>
                </p>
                <p>
                    <span style="font-family: &quot;Courier New&quot;; color: rgb(0, 0, 0); background-color: rgb(255, 255, 255);">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mailx&nbsp;[-BDdeEHiInNRv~]&nbsp;[-T&nbsp;name]&nbsp;[-A&nbsp;account]&nbsp;[-S&nbsp;variable[=value]]&nbsp;-f&nbsp;[name]</span>
                </p>
                <p>
                    <span style="font-family: &quot;Courier New&quot;; color: rgb(0, 0, 0); background-color: rgb(255, 255, 255);">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mailx&nbsp;[-BDdeEinNRv~]&nbsp;[-A&nbsp;account]&nbsp;[-S&nbsp;variable[=value]]&nbsp;[-u&nbsp;user]</span>
                </p>
                <p>
                    <span style="font-family: &quot;Courier New&quot;; color: rgb(0, 0, 0); background-color: rgb(255, 255, 255);">......</span>
                </p>
            </td>
        </tr>
    </tbody>
</table>
<p>
    <span style="font-size: 16px; color: rgb(0, 0, 255); background-color: rgb(255, 255, 255);">1、通过命令行发送邮件</span>
</p>
<p>
    <br/>
</p>
