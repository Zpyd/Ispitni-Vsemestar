

package com.mycompany.zad2_1kol2023_24;

import java.util.Stack;

public class Zad2_1kol2023_24 {

    public static void main(String[] args) {
        Stack<Integer> s=new Stack<>();
        s.push(2);
        s.push(2);
        s.push(1);
        s.push(1);
        s.push(2);
        s.push(3);
        s.push(3);
        s.push(4);
        s.push(2);
        s.push(3);
        s.push(1);
//        s.push(3);
//        s.push(3);
//        s.push(4);
//        s.push(2);
//        s.push(3);
//        s.push(1);
//        
    for (int element : s.reversed() ) {
            System.out.println(element);
        }
   
        System.out.println("\nsega drugio:\n");
        promeni(s);
        
       
    }

    private static void promeni(Stack<Integer> s) {
        
        Stack<Integer> pomStack=new Stack<>();
        
        
        int temp=s.pop();
        
        
        for (int i = 0; i < s.size();) {

            if (s.peek() == temp) {
                s.pop();
                pomStack.push(5);
                if (!s.empty()) {
                    temp = s.pop();
                }

            } else {
                pomStack.push(temp);
                if (!s.empty()) {
                    temp = s.pop();
                }
            }

        }
        if(pomStack.peek()==temp){
            pomStack.push(5);
        }else{
        pomStack.push(temp);
        }
          for (int element : pomStack.reversed() ) {
            System.out.println(element);
        }
   

       
}
}
