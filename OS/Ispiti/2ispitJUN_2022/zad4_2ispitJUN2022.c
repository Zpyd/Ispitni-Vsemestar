
#include<linux/module.h>
#include<linux/init.h>
#include <linux/fs.h>
#include <linux/sched.h>
#include <linux/errno.h>
#include <asm/current.h>
#include <asm/segment.h>
#include <asm/uaccess.h>

#define kluc1="juni123"
#define kluc2="juni!@#"
#define MEMSIZE 1000*8

bool locked=TRUE;
int mem[MEMSIZE]; 
int rezim; //0 za kluc1 1 za kluc2
int countK1=0;


bool is_key(char * buf){
    return !strcmp(kluc1,buff) || !strcmp(kluc2,buff); 

}


MODULE_AUTHOR("1262022");
MODULE_DESCRIPTION("zaklucen driver");
static int r_init(void);
static void r_cleanup(void);

module_init(r_init);
module_exit(r_cleanup);

static int my_open(struct inode *inode,struct file *filep);
static int my_release(struct inode *inode,struct file *filep);
static ssize_t my_read(struct file *filep,char *buff,size_t count,loff_t *offp );
static ssize_t my_write(struct file *filep,const char *buff,size_t count,loff_t *offp );

struct file_operations my_fops={
	open: my_open,
	read: my_read,
	write: my_write,
	release:my_release,
};



static int my_open(struct inode *inode, struct file *file)
{
printk("hello_open: successful\n");
return 0;
}
static int my_release(struct inode *inode, struct file *file)
{
printk("hello_release: successful\n");
return 0;
}
static int r_init(void)
{
    if(locked){-EACCES;}
    else{ 
        switch (rezim)
    {
    case 0:
        if(countK1==1){
            countK1=0;
            locked=TRUE;
        } countK1++;
        break;
    
    case 1:
        if(countK2==2){
            locked=TRUE;
            countK2=0;
            return 0;
        }
    default:
        break;
    }

    }
    
printk("<1>Zdravo ninji\n");
if(register_chrdev(60,"primer1",&my_fops)){
	printk("<1>nejke da registrira\n");
}
return 0;
}

static void r_cleanup(void)
{
    if(locked){-EACCES;}
    else{    
    switch (rezim)
    {
    case 0:
        if(countK1==1){
            countK1=0;
            locked=TRUE;
        } countK1++;
        break;
    
    case 1:
        if(countK2==2){
            locked=TRUE;
            countK2=0;
            return 0;
        }
    default:
        break;
    }


printk("<1>sajonara\n");
unregister_chrdev(60,"cprimer1");
return ;
}
}
static ssize_t my_read(struct file *file, char *buf,
size_t count,loff_t *ptr)
{

     if(locked){-EACCES;}
    else{ 
        switch (rezim)
    {
    case 0:
        if(countK1==1){
            countK1=0;
            locked=TRUE;
        } countK1++;
        break;
    
    case 1:
        if(countK2==2){
            locked=TRUE;
            countK2=0;
            return 0;
        }
    default:
        break;
    }
    }

    int citaj=w-r>=count?count:w-r;
    if(copy_to_user(buf,mem,citaj)){
    printk("<1> Kernel -> userspace kopiranjeto padna!\n" );
    return 0;
}
r+=citaj;
return citaj;
}
static ssize_t my_write(struct file *file, const char
*buf, size_t count,
loff_t * ppos)
{

 if(locked){
        if(is_key(buff)){
            if(kluc1){
                rezim=0;
         }else if(kluc2){
                countK2++;
                rezim=1;
         }
         else{
            -EACCES;
        }
        locked=FALSE;
        }
    }

    switch (rezim)
    {
    case 0:
        if(countK1==1){
            countK1=0;
            locked=TRUE;
        } countK1++;
        break;
    
    case 1:
        if(countK2==2){
            locked=TRUE;
            countK2=0;
            return 0;
        }
    default:
        break;
    }

int zapisi=80-w>=count?count:80-w;
if(copy_from_user(mem,buf,zapisi)){
printk("<1> UserSpace -> kernel kopiranjeto padna!\n" );
return 0;
};
w+=zapisi;
return zapisi;
}


MODULE_LICENSE("DUAL BSD/GPL");

