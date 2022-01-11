#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char valor[100];

int activo(char *variable)
{
    FILE *fp = fopen("/etc/vsftpd.conf", "r");
    if (fp == NULL)
    {
        perror("Unable to open file!");
    }
    int i, res = 0;
    char *fila = malloc(100 * sizeof(char));
    while (fgets(fila, 100, fp) != NULL)
    {
        for (i = 0; i < strlen(fila); i++)
        {
            if (fila[i] == variable[0])
            {
                if (strncmp(&fila[i], variable, strlen(variable)) == 0)
                {
                    if (fila[0] == '#')
                    {
                        res = 1;
                        break;
                    }
                }
            }
        }
    }
    fclose(fp);
    return res;
}

void valorVar(char resultado[], char variable[])
{
    FILE *fp = fopen("/etc/vsftpd.conf", "r");
    if (fp == NULL)
    {
        perror("Unable to open file!");
    }
    int cont = 0;
    char *fila = malloc(100 * sizeof(char));
    while (fgets(fila, 100, fp) != NULL)
    {
        for (int i = 0; i < strlen(fila); i++)
        {
            if (fila[i] == variable[0])
            {
                if (strncmp(&fila[i], variable, strlen(variable)) == 0)
                {
                    fila[strlen(fila) + 1] = '\0';
                    for (int j = 0; j < strlen(fila); j++)
                    {
                        if (fila[j] == '=')
                        {
                            for (int a = j + 1; a < strlen(fila) + 1; a++)
                            {
                                resultado[cont] = fila[a];
                                cont++;
                                if (fila[a] == '\0')
                                {
                                    resultado[cont + 1] = '\0';
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    fclose(fp);
}

int main(void)
{
    system("service vsftpd restart");
    printf("Content-type:text/html\n\n");
    printf("<html lang=\"en\">");
    printf("<head>");
    printf("<meta charset=\"UTF-8\">");
    printf("<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">");
    printf("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">");
    printf("<title>Administrador FTP</title>");
    printf("</head>");
    printf("<body>");
    printf("<style=\"font-family:'Lucida Sans', 'Lucida Sans Regular', 'Lucida Grande', 'Lucida Sans Unicode', Geneva, Verdana, sans-serif;\">");
    printf("<label style=\"font-size: 40px;\">General Settings</label>");
    printf("<div style=\"color: white; background-color: black;\">");
    printf("<label>Variable</label>");
    printf("<label style=\"position: relative; left: 150px;\">I/A</label>");
    printf("<label style=\"position: relative; left: 150px;\">Valor Variable</label>");
    printf("<label style=\"position: relative; left: 450px;\">Informacion</label>");
    printf("</div>");
    printf("<FORM ACTION=\"/cgi-bin/leerCo\" METHOD=\"POST\">");
    printf("<table border=\"1\">");
    printf("<tr>");
    printf("<td style=\"width: 210px;\"><label>write_enable</label></td>");
    if (activo("write_enable") == 1)
    {
        printf("<td><input type=\"checkbox\"></td>");
    }
    else
    {
        printf("<td><input type=\"checkbox\" checked></td>");
    }
    printf("<td>");
    printf("<select name=\"write_enable\" style=\"width: 100px;\">");
    valorVar(valor, "write_enable");
    if (strcmp(valor, "YES\n") == 0)
    {
        printf("<option selected>YES</option>");
        printf("<option>NO</option>");
    }
    else
    {
        printf("<option>YES</option>");
        printf("<option selected>NO</option>");
    }
    printf("</select>");
    printf("</td>");
    printf("<td style=\"width: 800px;\"><label>Al habilitar permite cualquier forma de comando de escrituraFTP</label>");
    printf("</td>");
    printf("</tr>");
    printf("<tr>");
    printf("<td><label>dirmessage_enable</label></td>");
    if (activo("dirmessage_enable") == 1)
    {
        printf("<td><input type=\"checkbox\"></td>");
    }
    else
    {
        printf("<td><input type=\"checkbox\" checked></td>");
    }
    printf("<td>");
    printf("<select name=\"dirmessage_enable\" style=\"width: 100px\">");
    valorVar(valor, "dirmessage_enable");
    if (strcmp(valor, "YES\n") == 0)
    {
        printf("<option selected>YES</option>");
        printf("<option>NO</option>");
    }
    else
    {
        printf("<option>YES</option>");
        printf("<option selected>NO</option>");
    }
    printf("</select>");
    printf("</td>");
    printf("<td><label>Activar mensajes de directorio: mensajes que se envían a usuarios remotos cuando ingresan a un directorio determinado.</label></td>");
    printf("</tr>");
    printf("<tr>");
    printf("<td><label>nopriv_user</label></td>");
    if (activo("nopriv_user") == 1)
    {
        printf("<td><input type=\"checkbox\"></td>");
    }
    else
    {
        printf("<td><input type=\"checkbox\" checked></td>");
    }
    printf("<td>");
    printf("<select name=\"nopriv_user\" style=\"width: 100px\">");
    valorVar(valor, "nopriv_user");
    if (strcmp(valor, "ftpSecure\n") == 0)
    {
        printf("<option selected>ftpSecure</option>");
        printf("<option>Nobody</option>");
    }
    else
    {
        printf("<option>ftpSecure</option>");
        printf("<option selected>Nobody</option>");
    }
    printf("</select>");
    printf("</td>");
    printf("<td><label>Se recomienda que defina en su sistema un usuario único que el servidor ftp puede utilizarlo como un usuario totalmente aislado y sin privilegios.</label></td>");
    printf("</tr>");
    printf("<tr>");
    printf("<td><label>ftpd_banner</label></td>");
    if (activo("ftpd_banner") == 1)
    {
        printf("<td><input type=\"checkbox\"></td>");
    }
    else
    {
        printf("<td><input type=\"checkbox\" checked></td>");
    }
    printf("<td>");
    valorVar(valor, "ftpd_banner");
    printf("<textarea style=\"width: 100px; height: 60px; resize: none;\">%s</textarea>", valor);
    printf("</td>");
    printf("<td><label>Puede personalizar completamente la cadena del banner de inicio de sesión.</label></td>");
    printf("</tr>");
    printf("<tr>");
    printf("<td><label>ls_recurse_enable</label></td>");
    if (activo("ls_recurse_enable") == 1)
    {
        printf("<td><input type=\"checkbox\"></td>");
    }
    else
    {
        printf("<td><input type=\"checkbox\" checked></td>");
    }
    printf("<td>");
    printf("<select style=\"width: 100px\">");
    valorVar(valor, "ls_recurse_enable");
    if (strcmp(valor, "YES\n") == 0)
    {
        printf("<option selected>YES</option>");
        printf("<option>NO</option>");
    }
    else
    {
        printf("<option>YES</option>");
        printf("<option selected>NO</option>");
    }
    printf("</select>");
    printf("</td>");
    printf("<td><label>Puede activar la opción \"-R\" en ls incorporado. Esto está deshabilitado por predeterminado para evitar que los usuarios remotos puedan causar E / S excesivas en grandes sitios. Sin embargo, algunos clientes FTP rotos como \"ncftp\" y \"mirror\" suponen la presencia de la opción \"-R\", por lo que hay un caso sólido para habilitarla.</label></td>");
    printf("</tr>");
    printf("<tr>");
    printf("<td><label>deny_email_enable<br>banned_email_file</label></td>");
    if (activo("deny_email_enable") == 1)
    {
        printf("<td><input type=\"checkbox\"><br>");
    }
    else
    {
        printf("<td><input type=\"checkbox\" checked><br>");
    }
    if (activo("banned_email_file") == 1)
    {
        printf("<input type=\"checkbox\"></td>");
    }
    else
    {
        printf("<input type=\"checkbox\" checked></td>");
    }
    printf("<td>");
    printf("<select style=\"width: 100px\">");
    valorVar(valor, "deny_email_enable");
    if (strcmp(valor, "YES\n") == 0)
    {
        printf("<option selected>YES</option>");
        printf("<option>NO</option>");
    }
    else
    {
        printf("<option>YES</option>");
        printf("<option selected>NO</option>");
    }
    valorVar(valor, "banned_email_file");
    printf("</select><br><input style=\"width: 100px\" type=\"text\" value=\"%s\">", valor);
    printf("</td>");
    printf("<td><label>Puede especificar un archivo de direcciones de correo electrónico anónimas no permitidas. Aparentemente útil para combatir ciertos ataques DoS.Ubicacion del archivo de correos baneados.</label></td>");
    printf("</tr>");
    printf("<tr>");
    printf("<td><label>hide_ids</label></td>");
    if (activo("hide_ids") == 1)
    {
        printf("<td><input type=\"checkbox\"></td>");
    }
    else
    {
        printf("<td><input type=\"checkbox\" checked></td>");
    }
    printf("<td>");
    printf("<select style=\"width: 100px\">");
    valorVar(valor, "hide_ids");
    if (strcmp(valor, "YES\n") == 0)
    {
        printf("<option selected>YES</option>");
        printf("<option>NO</option>");
    }
    else
    {
        printf("<option>YES</option>");
        printf("<option selected>NO</option>");
    }
    printf("</select>");
    printf("</td>");
    printf("<td><label>Si está habilitado, toda la información de usuarios y grupos en las listas de directorios se mostrará como \"ftp\".</label></td>");
    printf("</tr>");
    printf("</table>");
    printf("<label style=\"font-size: 40px;\">Local FTP user Settings</label>");
    printf("<div style=\"color: white; background-color: black;\">");
    printf("<label>Variable</label>");
    printf("<label style=\"position: relative; left: 150px;\">I/A</label>");
    printf("<label style=\"position: relative; left: 150px;\">Valor Variable</label>");
    printf("<label style=\"position: relative; left: 450px;\">Informacion</label>");
    printf("</div>");
    printf("<table border=\"1\">");
    printf("<tr>");
    printf("<td style=\"width: 210px;\"><label>local_enable</label></td>");
    if (activo("local_enable") == 1)
    {
        printf("<td><input type=\"checkbox\"></td>");
    }
    else
    {
        printf("<td><input type=\"checkbox\" checked></td>");
    }
    printf("<td>");
    printf("<select name=\"local_enable\" style=\"width: 100px\">");
    valorVar(valor, "local_enable");
    if (strcmp(valor, "YES\n") == 0)
    {
        printf("<option selected>YES</option>");
        printf("<option>NO</option>");
    }
    else
    {
        printf("<option>YES</option>");
        printf("<option selected>NO</option>");
    }
    printf("</select>");
    printf("</td>");
    printf("<td style=\"width: 800px;\"><label>Descomente esto para permitir que los usuarios locales inicien sesión.</label></td>");
    printf("</tr>");
    printf("<tr>");
    printf("<td><label>local_umask</label></td>");
    if (activo("local_umask") == 1)
    {
        printf("<td><input type=\"checkbox\"></td>");
    }
    else
    {
        printf("<td><input type=\"checkbox\" checked></td>");
    }
    valorVar(valor, "local_umask");
    printf("<td><input style=\"width: 100px;\" type=\"text\" value=\"%s\"></td>", valor);
    printf("<td><label>Activar mensajes de directorio: mensajes que se envían a usuarios remotos cuando ingresan a un directorio determinado.</label></td>");
    printf("</tr>");
    printf("<tr>");
    printf("<td><label>chroot_local_user<br>chroot_list_enable<br>chroot_list_file</label></td>");
    if (activo("chroot_local_user") == 1)
    {
        printf("<td><input type=\"checkbox\"><br>");
    }
    else
    {
        printf("<td><input type=\"checkbox\" checked><br>");
    }
    if (activo("chroot_list_enable") == 1)
    {
        printf("<input type=\"checkbox\"><br>");
    }
    else
    {
        printf("<input type=\"checkbox\" checked><br>");
    }
    if (activo("chroot_list_file") == 1)
    {
        printf("<input type=\"checkbox\"></td>");
    }
    else
    {
        printf("<input type=\"checkbox\" checked></td>");
    }
    printf("<td>");
    printf("<select name=\"chroot_local_user\" style=\"width: 100px\">");
    valorVar(valor, "chroot_local_user");
    if (strcmp(valor, "YES\n") == 0)
    {
        printf("<option selected>YES</option>");
        printf("<option>NO</option>");
    }
    else
    {
        printf("<option>YES</option>");
        printf("<option selected>NO</option>");
    }
    printf("</select><br><select name=\"hola\" style=\"width: 100px\">");
    valorVar(valor, "chroot_list_enable");
    if (strcmp(valor, "YES\n") == 0)
    {
        printf("<option selected>YES</option>");
        printf("<option>NO</option>");
    }
    else
    {
        printf("<option>YES</option>");
        printf("<option selected>NO</option>");
    }
    valorVar(valor, "chroot_list_file");
    printf("</select><br><input type=\"text\" style=\"width: 100px;\" value=\"%s\">", valor);
    printf("</td>");
    printf("<td><label>Puede especificar una lista explícita de usuarios locales para hacer chroot () a su casa directorio. Si chroot_local_user es SÍ, esta lista se convierte en una lista de que los usuarios NO hagan chroot ().</label></td>");
    printf("</tr>");
    printf("<tr>");
    printf("<td><label>allow_root_squashed_chroot</label></td>");
    if (activo("allow_root_squashed_chroot") == 1)
    {
        printf("<td><input type=\"checkbox\"></td>");
    }
    else
    {
        printf("<td><input type=\"checkbox\" checked></td>");
    }
    printf("<td>");
    printf("<select style=\"width: 100px\">");
    valorVar(valor, "allow_root_squashed_chroot");
    if (strcmp(valor, "YES\n") == 0)
    {
        printf("<option selected>YES</option>");
        printf("<option>NO</option>");
    }
    else
    {
        printf("<option>YES</option>");
        printf("<option selected>NO</option>");
    }
    printf("</select>");
    printf("</td>");
    printf("<td><label>Realiza chroot con credenciales originales (no root). Esto es útil en nfs con squash_root, donde root se convierte en nadie y necesitaría acceso -x.</label></td>");
    printf("</tr>");
    printf("<tr>");
    printf("<td><label>local_max_rate</label></td>");
    if (activo("local_max_rate") == 1)
    {
        printf("<td><input type=\"checkbox\"></td>");
    }
    else
    {
        printf("<td><input type=\"checkbox\" checked></td>");
    }
    valorVar(valor, "local_max_rate");
    printf("<td><input style=\"width: 100px\" type=\"text\" value=\"%s\"></td>", valor);
    printf("<td><label>La velocidad máxima de transferencia de datos permitida, en bytes por segundo, para usuarios autenticados locales. El valor predeterminado es 0 (ilimitado).</label></td>");
    printf("</tr>");
    printf("</table>");
    printf("<label style=\"font-size: 40px;\">Anonymus FTP user Settings</label>");
    printf("<div style=\"color: white; background-color: black;\">");
    printf("<label>Variable</label>");
    printf("<label style=\"position: relative; left: 150px;\">I/A</label>");
    printf("<label style=\"position: relative; left: 150px;\">Valor Variable</label>");
    printf("<label style=\"position: relative; left: 450px;\">Informacion</label>");
    printf("</div>");
    printf("<table border=\"1\">");
    printf("<tr>");
    printf("<td style=\"width: 210px;\"><label>anonymous_enable</label></td>");
    if (activo("anonymous_enable") == 1)
    {
        printf("<td><input type=\"checkbox\"></td>");
    }
    else
    {
        printf("<td><input type=\"checkbox\" checked></td>");
    }
    printf("<td>");
    printf("<select name=\"anonymous_enable\" style=\"width: 100px\">");
    valorVar(valor, "anonymous_enable");
    if (strcmp(valor, "YES\n") == 0)
    {
        printf("<option selected>YES</option>");
        printf("<option>NO</option>");
    }
    else
    {
        printf("<option>YES</option>");
        printf("<option selected>NO</option>");
    }
    printf("</select>");
    printf("</td>");
    printf("<td style=\"width: 800px;\"><label>¿Permitir FTP anónimo? (Cuidado: permitido de forma predeterminada si comenta esto).</label></td>");
    printf("</tr>");
    printf("<tr>");
    printf("<td><label>anon_max_rate</label></td>");
    if (activo("anon_max_rate") == 1)
    {
        printf("<td><input type=\"checkbox\"></td>");
    }
    else
    {
        printf("<td><input type=\"checkbox\" checked></td>");
    }
    valorVar(valor, "anon_max_rate");
    printf("<td><input style=\"width: 100px;\" type=\"text\" value=\"%s\"></td>", valor);
    printf("<td><label>La velocidad máxima de transferencia de datos permitida, en bytes por segundo, para usuarios autenticados. El valor predeterminado es 0 (ilimitado).</label></td>");
    printf("</tr>");
    printf("<tr>");
    printf("<td><label>anon_world_readable_only</label></td>");
    if (activo("anon_world_readable_only") == 1)
    {
        printf("<td><input type=\"checkbox\"></td>");
    }
    else
    {
        printf("<td><input type=\"checkbox\" checked></td>");
    }
    printf("<td>");
    printf("<select name=\"anon_world_readable_only\" style=\"width: 100px\">");
    valorVar(valor, "anon_world_readable_only");
    if (strcmp(valor, "YES\n") == 0)
    {
        printf("<option selected>YES</option>");
        printf("<option>NO</option>");
    }
    else
    {
        printf("<option>YES</option>");
        printf("<option selected>NO</option>");
    }
    printf("</select>");
    printf("</td>");
    printf("<td><label>Los usuarios anónimos solo podrán descargar archivos que sean legible en todo el mundo.</label></td>");
    printf("</tr>");
    printf("<tr>");
    printf("<td><label>anon_umask</label></td>");
    if (activo("anon_umask") == 1)
    {
        printf("<td><input type=\"checkbox\"></td>");
    }
    else
    {
        printf("<td><input type=\"checkbox\" checked></td>");
    }
    valorVar(valor, "anon_umask");
    printf("<td><input style=\"width: 100px;\" type=\"text\" value=\"%s\"></td>", valor);
    printf("<td><label>La máscara de usuario predeterminada para usuarios anónimos es 077. Es posible que desee cambiar esto a 022, si sus usuarios esperan eso (022 es usado por la mayoría de los otros ftpd)</label></td>");
    printf("</tr>");
    printf("<tr>");
    printf("<td><label>anon_upload_enable</label></td>");
    if (activo("anon_upload_enable") == 1)
    {
        printf("<td><input type=\"checkbox\"></td>");
    }
    else
    {
        printf("<td><input type=\"checkbox\" checked></td>");
    }
    printf("<td>");
    printf("<select style=\"width: 100px\">");
    valorVar(valor, "anon_upload_enable");
    if (strcmp(valor, "YES\n") == 0)
    {
        printf("<option selected>YES</option>");
        printf("<option>NO</option>");
    }
    else
    {
        printf("<option>YES</option>");
        printf("<option selected>NO</option>");
    }
    printf("</select>");
    printf("</td>");
    printf("<td><label>Descomente esto para permitir que el usuario FTP anónimo cargue archivos. Solo esto tiene un efecto si la habilitación de escritura global anterior está activada. Además, obviamente necesitará crear un directorio en el que el usuario FTP pueda escribir.</label></td>");
    printf("</tr>");
    printf("<tr>");
    printf("<td><label>anon_mkdir_write_enable</label></td>");
    if (activo("anon_mkdir_write_enable") == 1)
    {
        printf("<td><input type=\"checkbox\"></td>");
    }
    else
    {
        printf("<td><input type=\"checkbox\" checked></td>");
    }
    printf("<td>");
    printf("<select style=\"width: 100px\">");
    valorVar(valor, "anon_mkdir_write_enable");
    if (strcmp(valor, "YES\n") == 0)
    {
        printf("<option selected>YES</option>");
        printf("<option>NO</option>");
    }
    else
    {
        printf("<option>YES</option>");
        printf("<option selected>NO</option>");
    }
    printf("</select>");
    printf("</td>");
    printf("<td><label>Descomente esto si desea que el usuario FTP anónimo pueda crear nuevos directorios.</label></td>");
    printf("</tr>");
    printf("<tr>");
    printf("<td><label>anon_other_write_enable</label></td>");
    if (activo("anon_other_write_enable") == 1)
    {
        printf("<td><input type=\"checkbox\"></td>");
    }
    else
    {
        printf("<td><input type=\"checkbox\" checked></td>");
    }
    printf("<td>");
    printf("<select style=\"width: 100px\">");
    valorVar(valor, "anon_other_write_enable");
    if (strcmp(valor, "YES\n") == 0)
    {
        printf("<option selected>YES</option>");
        printf("<option>NO</option>");
    }
    else
    {
        printf("<option>YES</option>");
        printf("<option selected>NO</option>");
    }
    printf("</select>");
    printf("</td>");
    printf("<td><label>Descomente esto para permitir que los usuarios de FTP anónimos realicen otras operaciones de escritura. Como eliminación y cambio de nombre.</label></td>");
    printf("</tr>");
    printf("<tr>");
    printf("<td><label>chown_uploads<br>chown_username</label></td>");
    if (activo("chown_uploads") == 1)
    {
        printf("<td><input type=\"checkbox\"><br>");
    }
    else
    {
        printf("<td><input type=\"checkbox\" checked><br>");
    }
    if (activo("chown_username") == 1)
    {
        printf("<input type=\"checkbox\"></td>");
    }
    else
    {
        printf("<input type=\"checkbox\" checked></td>");
    }
    printf("<td>");
    printf("<select style=\"width: 100px\">");
    valorVar(valor, "chown_uploads");
    if (strcmp(valor, "YES\n") == 0)
    {
        printf("<option selected>YES</option>");
        printf("<option>NO</option>");
    }
    else
    {
        printf("<option>YES</option>");
        printf("<option selected>NO</option>");
    }
    valorVar(valor, "chown_username");
    printf("</select><br><input style=\"width: 100px;\" type=\"text\" value=\"%s\">", valor);
    printf("</td>");
    printf("<td><label>Si lo desea, puede hacer que los archivos anónimos subidos sean propiedad de un usuario diferente. ¡Nota! El uso de \"root\" para los archivos cargados no es recomendado!</label></td>");
    printf("</tr>");
    printf("</table>");
    printf("<label style=\"font-size: 40px;\">Log Settings</label>");
    printf("<div style=\"color: white; background-color: black;\">");
    printf("<label>Variable</label>");
    printf("<label style=\"position: relative; left: 150px;\">I/A</label>");
    printf("<label style=\"position: relative; left: 150px;\">Valor Variable</label>");
    printf("<label style=\"position: relative; left: 450px;\">Informacion</label>");
    printf("</div>");
    printf("<table border=\"1\">");
    printf("<tr>");
    printf("<td style=\"width: 210px;\"><label>syslog_enable</label></td>");
    if (activo("syslog_enable") == 1)
    {
        printf("<td><input type=\"checkbox\"></td>");
    }
    else
    {
        printf("<td><input type=\"checkbox\" checked></td>");
    }
    printf("<td>");
    printf("<select name=\"syslog_enable\" style=\"width: 100px\">");
    valorVar(valor, "syslog_enable");
    if (strcmp(valor, "YES\n") == 0)
    {
        printf("<option selected>YES</option>");
        printf("<option>NO</option>");
    }
    else
    {
        printf("<option>YES</option>");
        printf("<option selected>NO</option>");
    }
    printf("</select>");
    printf("</td>");
    printf("<td style=\"width: 800px;\"><label>Inicie sesión en el demonio syslog en lugar de utilizar un archivo de registro.</label></td>");
    printf("</tr>");
    printf("<tr>");
    printf("<td><label>log_ftp_protocol</label></td>");
    if (activo("log_ftp_protocol") == 1)
    {
        printf("<td><input type=\"checkbox\"></td>");
    }
    else
    {
        printf("<td><input type=\"checkbox\" checked></td>");
    }
    printf("<td>");
    printf("<select name=\"log_ftp_protocol\" style=\"width: 100px\">");
    valorVar(valor, "log_ftp_protocol");
    if (strcmp(valor, "YES\n") == 0)
    {
        printf("<option selected>YES</option>");
        printf("<option>NO</option>");
    }
    else
    {
        printf("<option>YES</option>");
        printf("<option selected>NO</option>");
    }
    printf("</select>");
    printf("</td>");
    printf("<td><label>Descomente esto para registrar todas las solicitudes y respuestas de FTP.</label></td>");
    printf("</tr>");
    printf("<tr>");
    printf("<td><label>xferlog_enable</label></td>");
    if (activo("xferlog_enable") == 1)
    {
        printf("<td><input type=\"checkbox\"></td>");
    }
    else
    {
        printf("<td><input type=\"checkbox\" checked></td>");
    }
    printf("<td>");
    printf("<select name=\"xferlog_enable\" style=\"width: 100px\">");
    valorVar(valor, "xferlog_enable");
    if (strcmp(valor, "YES\n") == 0)
    {
        printf("<option selected>YES</option>");
        printf("<option>NO</option>");
    }
    else
    {
        printf("<option>YES</option>");
        printf("<option selected>NO</option>");
    }
    printf("</select>");
    printf("</td>");
    printf("<td><label>Activar el registro de cargas / descargas.</label></td>");
    printf("</tr>");
    printf("<tr>");
    printf("<td><label>vsftpd_log_file</label></td>");
    if (activo("vsftpd_log_file") == 1)
    {
        printf("<td><input type=\"checkbox\"></td>");
    }
    else
    {
        printf("<td><input type=\"checkbox\" checked></td>");
    }
    valorVar(valor, "vsftpd_log_file");
    printf("<td><input name=\"vsftpd_log_file\" style=\"width: 100px;\" type=\"text\" value=\"%s\"></td>", valor);
    printf("<td><label>Puede anular dónde va el archivo de registro si lo desea. El valor predeterminado se muestra a continuación.</label></td>");
    printf("</tr>");
    printf("<tr>");
    printf("<td><label>xferlog_std_format</label></td>");
    if (activo("xferlog_std_format") == 1)
    {
        printf("<td><input type=\"checkbox\"></td>");
    }
    else
    {
        printf("<td><input type=\"checkbox\" checked></td>");
    }
    printf("<td>");
    printf("<select style=\"width: 100px\">");
    valorVar(valor, "xferlog_std_format");
    if (strcmp(valor, "YES\n") == 0)
    {
        printf("<option selected>YES</option>");
        printf("<option>NO</option>");
    }
    else
    {
        printf("<option>YES</option>");
        printf("<option selected>NO</option>");
    }
    printf("</select>");
    printf("</td>");
    printf("<td><label>Si lo desea, puede tener su archivo de registro en formato ftpd xferlog estándar. Tenga en cuenta que la ubicación predeterminada del archivo de registro es / var / log / xferlog en este caso.</label></td>");
    printf("</tr>");
    printf("<tr>");
    printf("<td><label>xferlog_file</label></td>");
    if (activo("xferlog_file") == 1)
    {
        printf("<td><input type=\"checkbox\"></td>");
    }
    else
    {
        printf("<td><input type=\"checkbox\" checked></td>");
    }
    valorVar(valor, "xferlog_file");
    printf("<td><input style=\"width: 100px;\" type=\"text\" value=\"%s\"></td>", valor);
    printf("<td><label>Puede anular dónde va el archivo de registro si lo desea. El valor predeterminado se muestra a continuación.</label></td>");
    printf("</tr>");
    printf("<tr>");
    printf("<td><label>dual_log_enable</label></td>");
    if (activo("dual_log_enable") == 1)
    {
        printf("<td><input type=\"checkbox\"></td>");
    }
    else
    {
        printf("<td><input type=\"checkbox\" checked></td>");
    }
    printf("<td>");
    printf("<select style=\"width: 100px\">");
    valorVar(valor, "dual_log_enable");
    if (strcmp(valor, "YES\n") == 0)
    {
        printf("<option selected>YES</option>");
        printf("<option>NO</option>");
    }
    else
    {
        printf("<option>YES</option>");
        printf("<option selected>NO</option>");
    }
    printf("</select>");
    printf("</td>");
    printf("<td><label>Habilite esto para tener archivos de registro de stand. Registro de estilo propio de xferlog y vsftpd estándar.</label></td>");
    printf("</tr>");
    printf("<tr>");
    printf("<td><label>setproctitle_enable</label></td>");
    if (activo("setproctitle_enable") == 1)
    {
        printf("<td><input type=\"checkbox\"></td>");
    }
    else
    {
        printf("<td><input type=\"checkbox\" checked></td>");
    }
    printf("<td>");
    printf("<select style=\"width: 100px\">");
    valorVar(valor, "setproctitle_enable");
    if (strcmp(valor, "YES\n") == 0)
    {
        printf("<option selected>YES</option>");
        printf("<option>NO</option>");
    }
    else
    {
        printf("<option>YES</option>");
        printf("<option selected>NO</option>");
    }
    printf("</select>");
    printf("</td>");
    printf("<td><label>Descomente esto para habilitar la información del estado de la sesión en la lista de procesos del sistema.</label></td>");
    printf("</tr>");
    printf("</table>");
    printf("<label style=\"font-size: 40px;\">Transfer Settings</label>");
    printf("<div style=\"color: white; background-color: black;\">");
    printf("<label>Variable</label>");
    printf("<label style=\"position: relative; left: 150px;\">I/A</label>");
    printf("<label style=\"position: relative; left: 150px;\">Valor Variable</label>");
    printf("<label style=\"position: relative; left: 450px;\">Informacion</label>");
    printf("</div>");
    printf("<table border=\"1\">");
    printf("<tr>");
    printf("<td style=\"width: 210px;\"><label>connect_from_port_20</label></td>");
    if (activo("connect_from_port_20") == 1)
    {
        printf("<td><input type=\"checkbox\"></td>");
    }
    else
    {
        printf("<td><input type=\"checkbox\" checked></td>");
    }
    printf("<td>");
    printf("<select name=\"connect_from_port_20\" style=\"width: 100px\">");
    valorVar(valor, "connect_from_port_20");
    if (strcmp(valor, "YES\n") == 0)
    {
        printf("<option selected>YES</option>");
        printf("<option>NO</option>");
    }
    else
    {
        printf("<option>YES</option>");
        printf("<option selected>NO</option>");
    }
    printf("</select>");
    printf("</td>");
    printf("<td style=\"width: 800px;\"><label>Asegúrese de que las conexiones de transferencia PORT se originen en el puerto 20 (ftp-data).</label></td>");
    printf("</tr>");
    printf("<tr>");
    printf("<td><label>idle_session_timeout</label></td>");
    if (activo("idle_session_timeout") == 1)
    {
        printf("<td><input type=\"checkbox\"></td>");
    }
    else
    {
        printf("<td><input type=\"checkbox\" checked></td>");
    }
    valorVar(valor, "idle_session_timeout");
    printf("<td><input style=\"width: 100px;\" type=\"text\" value=\"%s\"></td>", valor);
    printf("<td><label>Puede cambiar el valor predeterminado para el tiempo de espera de una sesión inactiva.</label></td>");
    printf("</tr>");
    printf("<tr>");
    printf("<td><label>data_connection_timeout</label></td>");
    if (activo("data_connection_timeout") == 1)
    {
        printf("<td><input type=\"checkbox\"></td>");
    }
    else
    {
        printf("<td><input type=\"checkbox\" checked></td>");
    }
    valorVar(valor, "data_connection_timeout");
    printf("<td><input style=\"width: 100px;\" type=\"text\" value=\"%s\"></td>", valor);
    printf("<td><label>Puede cambiar el valor predeterminado para el tiempo de espera de una conexión de datos.</label></td>");
    printf("</tr>");
    printf("<tr>");
    printf("<td><label>async_abor_enable</label></td>");
    if (activo("async_abor_enable") == 1)
    {
        printf("<td><input type=\"checkbox\"></td>");
    }
    else
    {
        printf("<td><input type=\"checkbox\" checked></td>");
    }
    printf("<td>");
    printf("<select style=\"width: 100px\">");
    valorVar(valor, "async_abor_enable");
    if (strcmp(valor, "YES\n") == 0)
    {
        printf("<option selected>YES</option>");
        printf("<option>NO</option>");
    }
    else
    {
        printf("<option>YES</option>");
        printf("<option selected>NO</option>");
    }
    printf("</select>");
    printf("</td>");
    printf("<td><label>Habilite esto y el servidor reconocerá las solicitudes ABORT asincrónicas. No recomendado por seguridad (el código no es trivial). Sin embargo, no habilitarlo puede confundir a los clientes FTP más antiguos.</label></td>");
    printf("</tr>");
    printf("<tr>");
    printf("<td><label>ascii_upload_enable<br>ascii_download_enable</label></td>");
    if (activo("ascii_upload_enable") == 1)
    {
        printf("<td><input type=\"checkbox\"><br>");
    }
    else
    {
        printf("<td><input type=\"checkbox\" checked><br>");
    }
    if (activo("ascii_download_enable") == 1)
    {
        printf("<input type=\"checkbox\"></td>");
    }
    else
    {
        printf("<input type=\"checkbox\" checked></td>");
    }
    printf("<td>");
    printf("<select name=\"ascii_upload_enable\" style=\"width: 100px\">");
    valorVar(valor, "ascii_upload_enable");
    if (strcmp(valor, "YES\n") == 0)
    {
        printf("<option selected>YES</option>");
        printf("<option>NO</option>");
    }
    else
    {
        printf("<option>YES</option>");
        printf("<option selected>NO</option>");
    }
    printf("</select><br>");
    printf("<select style=\"width: 100px\">");
    valorVar(valor, "ascii_download_enable");
    if (strcmp(valor, "YES\n") == 0)
    {
        printf("<option selected>YES</option>");
        printf("<option>NO</option>");
    }
    else
    {
        printf("<option>YES</option>");
        printf("<option selected>NO</option>");
    }
    printf("</select>");
    printf("</td>");
    printf("<td><label>Por defecto, el servidor pretenderá permitir el modo ASCII pero de hecho ignorará la solicitud. Active las siguientes opciones para que el servidor realmente manipule archivos ASCII cuando esté en modo ASCII. Tenga en cuenta que en algunos servidores FTP, el soporte ASCII permite un ataque de denegación de servicio (DoS) mediante el comando \"TAMAÑO / grande / archivo\" en modo ASCII. vsftpd predijo este ataque y siempre ha sido seguro, informando el tamaño del archivo RAW. La alteración de ASCII es una característica horrible del protocolo.</label></td>");
    printf("</tr>");
    printf("<tr>");
    printf("<td><label>pasv_enable</label></td>");
    if (activo("pasv_enable") == 1)
    {
        printf("<td><input type=\"checkbox\"></td>");
    }
    else
    {
        printf("<td><input type=\"checkbox\" checked></td>");
    }
    printf("<td>");
    printf("<select style=\"width: 100px\">");
    valorVar(valor, "pasv_enable");
    if (strcmp(valor, "YES\n") == 0)
    {
        printf("<option selected>YES</option>");
        printf("<option>NO</option>");
    }
    else
    {
        printf("<option>YES</option>");
        printf("<option selected>NO</option>");
    }
    printf("</select>");
    printf("</td>");
    printf("<td><label>Configúrelo en NO si desea rechazar el método PASV para obtener una conexión de datos.</label></td>");
    printf("</tr>");
    printf("<tr>");
    printf("<td><label>pam_service_name</label></td>");
    if (activo("pam_service_name") == 1)
    {
        printf("<td><input type=\"checkbox\"></td>");
    }
    else
    {
        printf("<td><input type=\"checkbox\" checked></td>");
    }
    valorVar(valor, "pam_service_name");
    printf("<td><input name=\"pam_service_name\" style=\"width: 100px;\" type=\"text\" value=\"%s\"></td>", valor);
    printf("<td><label>Configuración de PAM. ¡NO cambie esto a menos que sepa lo que hace!</label></td>");
    printf("</tr>");
    printf("<tr>");
    printf("<td><label>listen</label></td>");
    if (activo("listen") == 1)
    {
        printf("<td><input type=\"checkbox\"></td>");
    }
    else
    {
        printf("<td><input type=\"checkbox\" checked></td>");
    }
    printf("<td>");
    printf("<select style=\"width: 100px\">");
    valorVar(valor, "listen");
    if (strcmp(valor, "YES\n") == 0)
    {
        printf("<option selected>YES</option>");
        printf("<option>NO</option>");
    }
    else
    {
        printf("<option>YES</option>");
        printf("<option selected>NO</option>");
    }
    printf("</select>");
    printf("</td>");
    printf("<td><label>Cuando la directiva \"listen\" está habilitada, vsftpd se ejecuta en modo independiente y escucha en sockets IPv4. Esta directiva no se puede utilizar junto con la directiva listen ipv6.</label></td>");
    printf("</tr>");
    printf("<tr>");
    printf("<td><label>listen_ipv6</label></td>");
    if (activo("listen_ipv6") == 1)
    {
        printf("<td><input type=\"checkbox\"></td>");
    }
    else
    {
        printf("<td><input type=\"checkbox\" checked></td>");
    }
    printf("<td>");
    printf("<select name=\"listen_ipv6\" style=\"width: 100px\">");
    valorVar(valor, "listen_ipv6");
    if (strcmp(valor, "YES\n") == 0)
    {
        printf("<option selected>YES</option>");
        printf("<option>NO</option>");
    }
    else
    {
        printf("<option>YES</option>");
        printf("<option selected>NO</option>");
    }
    printf("</select>");
    printf("</td>");
    printf("<td><label>Esta directiva permite escuchar en sockets IPv6. Para escuchar en sockets IPv4 e IPv6, debe ejecutar dos copias de vsftpd con dos archivos de configuración. ¡¡Asegúrate de que una de las opciones de escucha esté comentada !!</label></td>");
    printf("</tr>");
    printf("<tr>");
    printf("<td><label>ssl_enable<br>rsa_cert_file<br>dsa_cert_file</label></td>");
    if (activo("ssl_enable") == 1)
    {
        printf("<td><input type=\"checkbox\"><br>");
    }
    else
    {
        printf("<td><input type=\"checkbox\" checked><br>");
    }
    if (activo("rsa_cert_file") == 1)
    {
        printf("<input type=\"checkbox\"><br>");
    }
    else
    {
        printf("<input type=\"checkbox\" checked><br>");
    }
    if (activo("dsa_cert_file") == 1)
    {
        printf("<input type=\"checkbox\"></td>");
    }
    else
    {
        printf("<input type=\"checkbox\" checked></td>");
    }
    printf("<td>");
    printf("<select name=\"ssl_enable\" style=\"width: 100px\">");
    valorVar(valor, "ssl_enable");
    if (strcmp(valor, "YES\n") == 0)
    {
        printf("<option selected>YES</option>");
        printf("<option>NO</option>");
    }
    else
    {
        printf("<option>YES</option>");
        printf("<option selected>NO</option>");
    }
    printf("</select>");
    valorVar(valor, "rsa_cert_file");
    printf("<br><input style=\"width: 100px;\" type=\"text\" value=\"%s\"><br>", valor);
    valorVar(valor, "dsa_cert_file");
    printf("<input style=\"width: 100px;\" type=\"text\" value=\"%s\"></td>", valor);
    printf("<td><label>Establezca \"ssl_enable = YES\" para habilitar la compatibilidad con SSL y configurar la ubicación de su certificado local (RSA, DSA o ambos). Tenga en cuenta que vsftpd no se iniciará si alguna de las opciones \" xxx_cert_file \" establece una ruta que no existe.</label></td>");
    printf("</tr>");
    printf("<tr>");
    printf("<td><label>pasv_min_port<br>pasv_max_port</label></td>");
    if (activo("pasv_min_port") == 1)
    {
        printf("<td><input type=\"checkbox\"><br>");
    }
    else
    {
        printf("<td><input type=\"checkbox\" checked><br>");
    }
    if (activo("pasv_max_port") == 1)
    {
        printf("<input type=\"checkbox\"></td>");
    }
    else
    {
        printf("<input type=\"checkbox\" checked></td>");
    }
    valorVar(valor, "pasv_min_port");
    printf("<td><input name=\"pasv_min_port\" style=\"width: 100px;\" type=\"text\" value=\"%s\">", valor);
    valorVar(valor, "pasv_max_port");
    printf("<br><input name=\"pasv_max_port\" style=\"width: 100px;\" type=\"text\" value=\"%s\"></td>", valor);
    printf("<td><label>Limite los puertos pasivos a este rango para ayudar al firewall</label></td>");
    printf("</tr>");
    printf("<tr>");
    printf("<td><label>isolate_network</label></td>");
    if (activo("isolate_network") == 1)
    {
        printf("<td><input type=\"checkbox\"></td>");
    }
    else
    {
        printf("<td><input type=\"checkbox\" checked></td>");
    }
    printf("<td>");
    printf("<select style=\"width: 100px\">");
    valorVar(valor, "isolate_network");
    if (strcmp(valor, "YES\n") == 0)
    {
        printf("<option selected>YES</option>");
        printf("<option>NO</option>");
    }
    else
    {
        printf("<option>YES</option>");
        printf("<option selected>NO</option>");
    }
    printf("</select>");
    printf("</td>");
    printf("<td><label>isolate_network asegura que el subproceso vsftpd se inicia en el propio espacio de nombres de la red (consulte CLONE_NEWNET en el clon (2)). Sin embargo, deshabilita los métodos de autenticación que necesitan el acceso a la red (LDAP, NIS, ...).</label></td>");
    printf("</tr>");
    printf("<tr>");
    printf("<td><label>seccomp_sandbox</label></td>");
    if (activo("seccomp_sandbox") == 1)
    {
        printf("<td><input type=\"checkbox\"></td>");
    }
    else
    {
        printf("<td><input type=\"checkbox\" checked></td>");
    }
    printf("<td>");
    printf("<select style=\"width: 100px\">");
    valorVar(valor, "seccomp_sandbox");
    if (strcmp(valor, "YES\n") == 0)
    {
        printf("<option selected>YES</option>");
        printf("<option>NO</option>");
    }
    else
    {
        printf("<option>YES</option>");
        printf("<option selected>NO</option>");
    }
    printf("</select>");
    printf("</td>");
    printf("<td><label>seccomp_sanbox agrega una capa de seguridad adicional que limita el número de llamadas al sistema que se pueden realizar a través de vsftpd. Sin embargo, puede suceder que una lista blanca no permita una llamada legítima (generalmente activada indirectamente por una biblioteca de terceros como pam o openssl) y el kernel mata el proceso. Por lo tanto, si su servidor muere en situaciones comunes (descarga de archivos, carga), elimine el comentario de la siguiente línea y no olvide abrir el error en https://bugzilla.novell.com</label></td>");
    printf("</tr>");
    printf("</table>");
    printf("<INPUT TYPE=\"SUBMIT\" VALUE=\"Send\">");
    printf("</FORM>");
    printf("</body>");
    printf("</html>");
}