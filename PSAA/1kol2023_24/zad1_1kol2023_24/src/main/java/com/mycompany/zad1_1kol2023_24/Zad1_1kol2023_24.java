
package com.mycompany.zad1_1kol2023_24;

public class Zad1_1kol2023_24 {

    
    /*
    
        Nedovrsena -> treba da se srede logikata
                     +Da se dodae nova print so ke gi printa kako so treba per vagon
                     
                     mn vreme zadacata odzima
    
    
    */
    
    
    public static class Voz{
        int brVagoni;
        int brPrvaKlasaVag;
        int brEconomyKlasaVag;
        int maxPerVagon=20;
        SLinkedList<Patnik> vagoni =new SLinkedList<>();
            Voz(int brV,int brPrvaKlasa){
                this.brPrvaKlasaVag=brPrvaKlasa;
                this.brVagoni=brV;
                this.brEconomyKlasaVag=brVagoni-brPrvaKlasaVag;
        };
    };
    
    public static class Karta{
        int cardNum;
        boolean prvaKlasa; 
        
        Karta(int cbr,boolean pk){
            this.cardNum=cbr;
            this.prvaKlasa=pk;
        }
    }
    
    public static class Patnik{
        String ime, prezime;
        Karta k;    
        
        Patnik(String im,String prez, Karta k){
            this.ime=im;
            this.prezime=prez;
            this.k=k;
        }
    }
    
    
    public static void smestiPatniciVoz(Voz v, Patnik[] p){
       
        
        int brPatnici=p.length; 
        int brPrvaKP=0; 
        for (int i = 0; i < brPatnici; i++) { //ik ne e najoptimalno ama time crunch
            if(p[i].k.prvaKlasa){
                brPrvaKP++;
            }
        }
        int brEconomyKP=brPatnici-brPrvaKP;
        
        
        //math.ceil da ne se ispustat people poso za zal nemozeme da gi iseceme na pola i da gi staeme ako ima 6.5 people per vagon
        int brPerVagonEKP=(int)Math.ceil(v.brEconomyKlasaVag/brEconomyKP);//voa nikad ne treba da bide >20 pso ako bide tie so prodavat karti zaebale rabota
        int brPerVagonPKP=(int)Math.ceil(v.brPrvaKlasaVag/brPrvaKP);
        
        Patnik[] prvaKlasaPatnici= new Patnik[brPrvaKP];
        
        for (int i = 0; i < p.length; i++) {
            int Ecounter=0; int Pcounter=0;//
            if(!p[i].k.prvaKlasa){
                if(Ecounter<brPerVagonEKP){
                    
                    Ecounter++;
                }
          
                else{
                    v.vagoni.insertLast(p[i]);
                    Ecounter=1;
                }
                
                
            }
            else{
                     prvaKlasaPatnici[Pcounter++]=p[i];   
                        }
        }

       
        //so ako imame povise od mozni smestuvanja u vagoni? -> pretpostavka nema da se dese radi tie so prodavat karti e odg toa
        
        
        
        for (int i = 0; i < v.brPrvaKlasaVag; i++) {
            int Pcounter = 0;
            if (Pcounter < brPerVagonPKP) {
                v.vagoni.insertLast(prvaKlasaPatnici[i]);
                Pcounter++;
        }
             else{
                    v.vagoni.insertLast(prvaKlasaPatnici[i]);
                    Pcounter=1;
                
        }
        
    }
    
 }
    public static void main(String[] args) {
        System.out.println("Hello World!");
        
        Karta k1=new Karta(135,true);
        Karta k2=new Karta(136,false);
        Karta k3=new Karta(137,false);
        Karta k4=new Karta(138,true);
        Karta k5=new Karta(139,false);
        
        Patnik p[]= new Patnik[5];
        p[0].ime="Im"; p[0].prezime="done"; p[0].k=k1;
        p[1].ime="Im"; p[1].prezime="done"; p[1].k=k1;
        p[2].ime="Im"; p[2].prezime="done"; p[2].k=k1;
        p[3].ime="Im"; p[3].prezime="done"; p[3].k=k1;
        
        Voz v= new Voz(4,1);
        
    }
    
    //Node=vagon
    static class Node<E> {
    protected E[] Passenger= (E[]) new Object[20];
    protected Node<E> next;
    protected int maxNumPassengers=20;
    protected int brP=0;
    
    public Node() {
        for (int i = 0; i < maxNumPassengers; i++) {
            Passenger[i] = null;
        }
        
        next = null;
    }
    
    
    
    public Node(E data, Node<E> next) {
        this.Passenger[0]=data;
        this.next = next;
    }
    
    public void insertPassenger(E p){
        if (brP<20){
            Passenger[brP++]=p;
        }
        else System.out.println("Preoptovaren e vaj vagon stavi nov baki");
    }
}

static class SLinkedList<E> {
    private Node<E> head;
    
    public Node<E> getHead() {
        return head;
    }
    
    public SLinkedList() {
        head = null;
    }
    
    public void insertFirst(E e) {
        Node<E> first = new Node(e, head);
        head = first;
    }
    
    public void insertAfter(E e, Node<E> n) {
        if (n != null) {
            Node<E> node = new Node(e, n.next);
            n.next = node;
        } else {
            System.out.println("Error.");
        }
    }
    
    public void insertBefore(E e, Node<E> n) {
        if (head != null) {
            Node<E> tmp = head;
            if (tmp == n) {
                this.insertFirst(e);
                return;
            }
            
            while(tmp.next != n && tmp.next != null) {
                tmp = tmp.next;
            }
            
            if (tmp.next == n) {
                Node<E> node = new Node(e, n);
                tmp.next = node;
            }
        }
    }
    
    public void insertLast(E e) {
        if (head != null) {
            Node<E> tmp = head;
            while (tmp.next != null) {
                tmp = tmp.next;
            }
            
            Node<E> last = new Node(e, null);
            tmp.next = last;
        } else {
            this.insertFirst(e);
        }
    }
    
    public void deleteFirst() {
        if (head != null) {
            head = head.next;
        } else {
            System.out.println("Error.");
        }
    }
    
    public void printList() {
        Node<E> tmp = head;
        
        while (tmp.next != null) {
            System.out.print(tmp.data + " -> ");
            tmp = tmp.next;
        }
        System.out.println(tmp.data);
    }
    
    public void reverse() {
        if (head != null) {
            Node<E> curr = head;
            Node<E> prev = null, next = null;
            
            while (curr != null) {
                next = curr.next;
                curr.next = prev;
                prev = curr;
                curr = next;
            }
            
            head = prev;
        }
    }
}
}
