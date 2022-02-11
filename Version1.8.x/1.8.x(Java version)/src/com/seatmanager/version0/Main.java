package com.seatmanager.version0;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) throws IOException {
        SeatManagerImp workSpace = new SeatManagerImp();
        boolean isExit = false;
        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));
        while (!isExit) {
            workSpace.showUI();
            Scanner scanner = new Scanner(System.in);
            System.out.println("请输入你的选择：");
            int select = Integer.parseInt(bufferedReader.readLine());
            switch (select) {
                case 0 -> isExit = true;
                case 1 -> workSpace.creatTable();
                case 2 -> workSpace.showTable();
                case 3 -> workSpace.deleteTable(bufferedReader);
            }
        }
        bufferedReader.close();
    }
}
