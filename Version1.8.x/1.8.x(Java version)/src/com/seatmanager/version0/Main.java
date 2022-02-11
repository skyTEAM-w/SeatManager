package com.seatmanager.version0;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) throws IOException {
        boolean isExit = false;
        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));
        while (!isExit) {
            SeatManagerImp.showUI();
            Scanner scanner = new Scanner(System.in);
            System.out.println("请输入你的选择：");
            char select = (char)bufferedReader.read();
            switch (select) {
                case '0' -> isExit = true;
                case '1' -> SeatManagerImp.creatTable();
                case '2' -> SeatManagerImp.showTable();
            }
        }
        bufferedReader.close();
    }
}
