package com.whu;

import java.sql.*;

public class DBTest {
    private Connection conn;
    private String user = "test";
    private String password = "test";
    private String className="oracle.jdbc.driver.OracleDriver";
    private String url = "jdbc:oracle:thin:@localhost:1521:XE";

    //加载数据库驱动
    public void ConnectOracle(){
        try{
            Class.forName(className); //加载Oracle驱动
            System.out.println("驱动加载成功!");
        }catch (ClassNotFoundException e) {
            System.out.println("驱动加载错误!");
            e.printStackTrace();//打印出错详细信息
        }
    }

    //创建数据库连接
    public Connection getConn(){
        try{
            conn = DriverManager.getConnection(url,user,password);
            System.out.println("数据库连接成功！");
        } catch (SQLException e) {
            System.out.println(conn);
            System.out.println("数据库连接错误");
            conn=null;
            e.printStackTrace();
        }
        return conn;
    }

    //关闭数据库连接
    public void closed(){
        try {
            if(conn != null) conn.close();

        } catch(Exception e) {
            System.out.println("数据库关闭错误");
            e.printStackTrace();
        }
        conn = null;
    }


	public static void main(String[] args) {
        DBTest d =new DBTest();
        d.ConnectOracle();
        d.getConn();
        d.closed();
    }
  

}
