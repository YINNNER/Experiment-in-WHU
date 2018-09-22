package com.whu;

import java.io.IOException;
import java.util.List;
import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class DBServlet extends HttpServlet{
    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        // 创建数据库连接及JDBC对象
        DBTest db = new DBTest();
        DBOperation dbOperation = new DBOperation();
        db.ConnectOracle();
        dbOperation.setConn(db.getConn());

        // 获得数据库所有表信息
        List<DBTable> tables = dbOperation.getTables();

        // 获得index.jsp传来的选项
        String operate = request.getParameter("type");

        request.setAttribute("operate",operate);
        request.setAttribute("tables",tables);


        //关闭JDBC对象及关闭数据库连接
        dbOperation.closed();
        db.closed();

        //请求jsp页面
        RequestDispatcher view = request.getRequestDispatcher("index.jsp");
        view.forward(request,response);


    }

    public void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        doGet(request, response);
    }
}
