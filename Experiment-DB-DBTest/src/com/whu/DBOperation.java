package com.whu;

import java.sql.*;
import java.util.*;

public class DBOperation {
    private PreparedStatement pstmt;
    private ResultSet rs;
    private String sql;
    private Connection conn;
    private String errorInfo = null;

    public String getErrorInfo() {
        return errorInfo;
    }

    public void setErrorInfo(String errorInfo) {
        this.errorInfo = errorInfo;
    }

    public void setConn(Connection conn) {
        this.conn = conn;
    }

    public void closed(){
        if (rs != null){ // 关闭记录集
            try {
                rs.close();
            }catch (SQLException e){
                e.printStackTrace();
            }
        }
        if (pstmt != null){ // 关闭声明
            try {
                pstmt.close();
            }catch (SQLException e){
                e.printStackTrace();
            }
        }

    }

    private void prepareStmt(){
        try {
            pstmt = conn.prepareStatement(sql);
        }catch (SQLException e){
            System.out.println("创建语句失败！");
            e.printStackTrace();
            String error_raw = e.getMessage().toString().substring(11);
            setErrorInfo(error_raw);
        }
    }

    private boolean executeUpdateSql(){
        try {
            int status = pstmt.executeUpdate();
            System.out.println("数据更新成功！");
            return true;
        }catch (SQLException e){
            System.out.println("数据更新失败！");
            e.printStackTrace();
            String[] error_raw = e.getMessage().toString().substring(11).split("\n",2);
            setErrorInfo(error_raw[0]);
            return false;
        }

    }

    private boolean executeQuerySql(){
        try {
            rs = pstmt.executeQuery();
            System.out.println("数据查询成功！");
            return true;
        }catch (SQLException e){
            System.out.println("数据查询失败！");
            e.printStackTrace();
            String error_raw = e.getMessage().toString().substring(11);
            setErrorInfo(error_raw);
            return false;
        }

    }

    private List<String> handleResult(){
        List<String> result=new ArrayList<>();
        String name="";
        try {
            while (rs.next()){
                for (int i = 1; i <= rs.getMetaData().getColumnCount(); i++){
                    if (i!=rs.getMetaData().getColumnCount()) name += rs.getString(i)+",";
                    else name += rs.getString(i);
                }
                result.add(name);
                name = "";
            }
        }catch (SQLException e){
            System.out.println("数据操作失败！");
            e.printStackTrace();
        }
        return result;
    }

    public boolean insertData(String table, String[] list, int colNum){
        boolean success = false;
        String [] sqlList = new String[list.length/colNum];
        for (int j=0; j<list.length/colNum; j++){
            sqlList[j] = "INSERT INTO " + table + " VALUES (";
            for (int i=j*colNum; i<(j+1)*colNum; i++){
                if (!list[i].equals("")){
                    if (i != (j+1)*colNum-1) sqlList[j] += "\'" + list[i] + "\',";
                    else sqlList[j] += "\'" + list[i] + "\')";
                }
                else {
                    if (i != (j+1)*colNum-1) sqlList[j] += "NULL,";
                    else sqlList[j] += "NULL)";
                }
            }
        }
        try {
            conn.setAutoCommit(false);
            for (String s:sqlList){
                sql = s;
                prepareStmt();
                if (!executeUpdateSql()){
                    conn.rollback();
                    return success;
                }
            }
            conn.commit();
            success = true;
        }
        catch (SQLException e){
            success = false;
        }

        return success;
    }

    public boolean updateData(String table, String setCondition, String condition){
        sql="UPDATE " + table + " SET " + setCondition + " WHERE "+ condition;
        prepareStmt();
        return executeUpdateSql();
    }

    public boolean deleteData(String table, String condition){
        sql="DELETE from " + table + " WHERE " + condition;
        prepareStmt();
        return executeUpdateSql();
    }

    public List<String> simpleQuery(String table, String condition){
        if (condition == null) sql = "SELECT * FROM " + table;
        else sql = "SELECT * FROM " + table + " WHERE " + condition;
        prepareStmt();
        if (!executeQuerySql()) return null;

        return handleResult();
    }

    public List<DBTable> getTables(){
        // get tables' names
        List<DBTable> tables = new ArrayList<>();
        DBTable table;
        List<String> tableNames;
        sql = "select table_name from user_tables";
        prepareStmt();
        if (!executeQuerySql()) return null;
        tableNames = handleResult();

        // get tables' column names
        // add DBTable objects to list
        for (String tableName : tableNames){
            table = new DBTable();
            table.setTableName(tableName);

            sql="SELECT * FROM " + tableName;
            prepareStmt();
            executeQuerySql();
            table.setColName(getColumnName());
            table.setIsColumnsNullable(isColumnsNullable());

            tables.add(table);
        }
        return tables;
    }

    // sql在别的函数中赋值
    public List<String> getColumnName(){
        ResultSetMetaData metaData;
        List<String> columns=new ArrayList<>();
        try {
            metaData = rs.getMetaData();
            for (int i = 1; i <= metaData.getColumnCount(); i++){
                columns.add(metaData.getColumnName(i));
            }
        }catch (SQLException e){
            System.out.println("查询元数据失败！");
            e.printStackTrace();
            return null;
        }
        return columns;
    }

    // 判断字段是否能为空
    private List<Integer> isColumnsNullable (){
        List<Integer> isColumnsNullable = null;
        ResultSetMetaData metaData;
        try {
            metaData = rs.getMetaData();
            isColumnsNullable = new ArrayList<>(metaData.getColumnCount());
            for (int i = 1; i <= metaData.getColumnCount(); i++){
                isColumnsNullable.add(metaData.isNullable(i));
            }
        }catch (SQLException e){
            System.out.println("查询元数据失败！");
            e.printStackTrace();
            return null;
        }
        return isColumnsNullable;
    }



}
