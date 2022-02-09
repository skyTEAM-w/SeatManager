package com.seatmanager.version0;

public class Student {
    private String Name;
    private String id;

    public Student() {
    }

    public Student(String name, String id) {
        Name = name;
        this.id = id;
    }

    public String getName() {
        return Name;
    }

    public void setName(String name) {
        Name = name;
    }

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }
}
