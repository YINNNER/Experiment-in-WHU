package com.whu;

import java.util.List;

public class DBTable {
    public String tableName;
    public List<String> colName;
    public List<Integer> isColumnsNullable;

    public String getTableName() {
        return tableName;
    }

    public List<String> getColName() {
        return colName;
    }

    public List<Integer> getIsColumnsNullable() {
        return isColumnsNullable;
    }

    public void setIsColumnsNullable(List<Integer> isColumnsNullable) {
        this.isColumnsNullable = isColumnsNullable;
    }

    public void setTableName(String tableName) {
        this.tableName = tableName;
    }

    public void setColName(List<String> colName) {
        this.colName = colName;
    }

}
