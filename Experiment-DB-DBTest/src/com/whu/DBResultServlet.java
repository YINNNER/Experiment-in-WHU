package com.whu;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.List;

public class DBResultServlet extends HttpServlet{
    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        // 创建数据库连接及JDBC对象
        DBTest db = new DBTest();
        DBOperation dbOperation = new DBOperation();
        db.ConnectOracle();
        dbOperation.setConn(db.getConn());

        // 获得index.jsp传来的选项
        String status = "";
        String errorInfo = null;
        List<String> result = null;
        List<String> columnNames = null;
        String operate = request.getParameter("type");
        String table = request.getParameter("table-name");
        String column = null;
        String colValue = null;
        String condition = null;


        switch (operate){
            case "query":
                column = request.getParameter("column-name");
                colValue = request.getParameter("col-value");
                if (!colValue.equals("")) condition = column + "=\'" + colValue + "\'";
                if ((result=dbOperation.simpleQuery(table,condition))!=null){
                    if (result.size()== 0){
                        status = "查询结果不存在!";
                    } else {
                        columnNames = dbOperation.getColumnName();
                        status = "查询结果如下：";
                    }

                }
                else {
                    status="查询数据失败!";
                    errorInfo = dbOperation.getErrorInfo();
                }
                break;

            case "insertData":
                int colNum = Integer.parseInt(request.getParameter("colNum"));
                if (dbOperation.insertData(table, request.getParameterValues("col-value"), colNum)){
                    status="成功插入数据!";
                    result = dbOperation.simpleQuery(table,null);
                    columnNames = dbOperation.getColumnName();
                }
                else {
                    status = "插入数据失败!";
                    errorInfo = dbOperation.getErrorInfo();
                }
                break;

            case "updateData":
                String setCondition = request.getParameterValues("column-name")[1] + "=\'"
                        + request.getParameterValues("col-value")[1] + "\'";

                column = request.getParameterValues("column-name")[0];
                colValue = request.getParameterValues("col-value")[0];
                condition = column + "=\'" + colValue + "\'";

                if (dbOperation.updateData(table, setCondition, condition)){
                    status="成功更新数据!";
                    result = dbOperation.simpleQuery(table,condition);
                    columnNames = dbOperation.getColumnName();
                }
                else {
                    status = "更新数据失败!";
                    errorInfo = dbOperation.getErrorInfo();
                }
                break;

            case "deleteData":
                column = request.getParameter("column-name");
                colValue = request.getParameter("col-value");

                condition = column + "=\'" + colValue + "\'";
                if (dbOperation.deleteData(table,condition)){
                    status="成功删除数据!";
                    result = dbOperation.simpleQuery(table,null);
                    columnNames = dbOperation.getColumnName();
                }
                else {
                    status = "删除数据失败!";
                    errorInfo = dbOperation.getErrorInfo();
                }
                break;

            default:
                break;
        }

        request.setAttribute("operate",operate);
        request.setAttribute("status",status);
        request.setAttribute("error",errorInfo);
        request.setAttribute("result",result);
        request.setAttribute("tableName",table);
        request.setAttribute("columnNames",columnNames);

        //关闭JDBC对象及关闭数据库连接
        dbOperation.closed();
        db.closed();

        //请求jsp页面
        RequestDispatcher view = request.getRequestDispatcher("result.jsp");
        view.forward(request,response);
    }

    public void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        doGet(request, response);
    }
}
