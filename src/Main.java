import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.Scanner;

/*
create database dlxflwpwr;

create user 'dlxflwpwr'@'localhost' identified by 'dlxflwpwr';

create table dlxflwpwr(id int not null auto_increment, time timestamp default current_timestamp, data char(32), primary key (id));
 */

public class Main {

    public static void main(String[] args) {

        for (int i = 0; i < 10; i++) {

            try {
                String command = "echo hejs";
                Process p = new ProcessBuilder("/bin/sh", "-c", command).start();
                Scanner sc = new Scanner(p.getInputStream());
                storeData(sc.nextLine());
                Thread.sleep(1000);
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }

    private static void storeData(String data) {

        String url = "jdbc:mariadb://localhost:3306/dlxflwpwr";
        String user = "dlxflwpwr";
        String password = "dlxflwpwr";

        Connection con = null;
        Statement stmt = null;

        try {
            Class.forName("org.mariadb.jdbc.Driver");
            con = DriverManager.getConnection(url, user, password);
            stmt = con.createStatement();
            stmt.executeQuery("INSERT INTO dlxflwpwr(data) VALUES('" + data + "');");

        } catch (Exception e) {
            System.out.println(e);
        } finally {
            try {
                if (stmt != null)
                    stmt.close();
                if (con != null)
                    con.close();
            } catch (SQLException e) {
                System.out.println(e);
            }
        }

    }
}