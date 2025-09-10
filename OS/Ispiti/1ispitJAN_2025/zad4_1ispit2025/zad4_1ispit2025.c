#include<linux/module.h>
#include<linux/init.h>
#include <linux/fs.h>
#include <linux/sched.h>
#include <linux/errno.h>
#include <asm/current.h>
#include <asm/segment.h>
#include <asm/uaccess.h>
MODULE_AUTHOR("ackata");
MODULE_DESCRIPTION("virtuelen driver");

#define MNAME "ured1"
#define BUFFER 6*1000
#define BUFFER2 4*1000

static int content_size=0;
static int more_space_needed=0;
static char glavna_mem[BUFFER];
static char pomosna_mem[BUFFER2];

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
printk("<1>hello_open: successful\n");
return 0;
}
static int my_release(struct inode *inode, struct file *file)
{
printk("hello_release: successful\n");
return 0;
}
static int r_init(void)
{
printk("<1>Zdravo ninji\n");
if(register_chrdev(60, MNAME,&my_fops)){
	printk("<1>nejke da registrira\n");
}
return 0;
}
static void r_cleanup(void)
{
printk("<1>sajonara\n");
unregister_chrdev(60,MNAME);
return ;
}

static ssize_t my_read(struct file *file, char *buf,
size_t count,loff_t *ptr)
{
    if(*ptr>content_size){
        printk("nema vise za citanje");
        return 0;
    }
    if(*ptr>BUFFER){
       
        if(count>BUFFER+BUFFER2-*ptr){ 
            count=BUFFER+BUFFER2-*ptr;
        }
        if(copy_to_user(buf,pomosna_mem+*ptr-BUFFER,count))
    return -EFAULT;
    
        *ptr+=count;

        return 0;

    }

    if(count>BUFFER-*ptr){
        count = BUFFER-*ptr;
    }

    if(copy_to_user(buf,glavna_mem+*ptr,count))
    return -EFAULT;

    *ptr+=count;

    return 0;
}
static ssize_t my_write(struct file *file, const char
*buf, size_t count,
loff_t * ppos)
{
    if (count>BUFFER-*ppos){
        more_space_needed+=1;
        if(more_space_needed>=3){
            if(count>BUFFER+BUFFER2-*ppos){
                printk("<1> Korisniko ja iskoristi celata memorija alal neka mu e ");
                return 0;
            }
            if(copy_from_user(pomosna+*ptr-BUFFER,buf,count))
            return -EFAULT

            *ppos+=count;
            content_size+=count;
            printk(KERN_INFO "%s: wrote %zu bytes\n u pomosna", MNAME, count);
            return count;
        }
        printk("<1> Korisniko probal %d da vnese neuspesno u glavna memorija", more_space_needed);
        return 0;
    }

    if(copy_from_user(dev_content+*ptr,buf,count))
    return -EFAULT
    *ppos+=count;
    content_size+=count;
    printk(KERN_INFO "%s: wrote %zu bytes\n u glavna", MNAME, count);
    return count;

}
MODULE_LICENSE("DUAL BSD/GPL");
