//Chrystal Mingo
//Operating System
//Project - Driver

/* driver_proj.c − The simplest kernel module. */

#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/vmalloc.h>
#include <linux/hdreg.h>
#include <linux/blkdev.h>
#include <linux/genhd.h>
#include <linux/errno.h>
#include <linux/types.h>

MODULE_LICENSE("Dual BSD/GPL");

static int hardsect_size = 512;
static int nsectors = 1024;	/* How big the drive is */

#define NR_SECTORS                   1024
#define KERNEL_SECTOR_SIZE           512


static struct block_dev{
    int size;                       /* Device's size in sectors */
    u8 *data;                       /* Array of Data */
    short users;
    short media_change;
    spinlock_t lock;                /* MUTEX */
    struct gendisk *gd;             /* gendisk structure*/
    struct request_queue *queue;    /* The Device's request queue */
    struct timer_list timer;         /* For Simulated media changes */
} dev;


static int block_open(struct block_device *bdev, fmode_t mode){
    printk(KERN_INFO "Block open called !!!.\n");
    return 0;
}


static void release (struct gendisk *gd, fmode_t mode){
    printk(KERN_INFO "Block release called !!!.\n");
    return;
}

static struct block_device_operations sbull_ops = {
        .owner = THIS_MODULE,
        .open = block_open,
        .release = release
};


static void request(struct request_queue *q){
    printk(KERN_INFO "Request processing.\n");
}

static int create_block_device(struct block_dev *dev){
    /*allocate memory */
    memset(dev, 0, sizeof(struct block_dev));
    dev->size = nsectors*hardsect_size;
    dev->data = vmalloc(dev->size);
    if(dev->data == NULL){
        printk(KERN_NOTICE "vmalloc failure.\n");
        return -ENOMEM;
    }
    spin_lock_init(&dev->lock);

    //blk_init_queue implicitly declared
    dev->queue = blk_init_queue(request, &dev->lock);
    /* Initialize the gendisk structure */

    dev->gd = alloc_disk(1);
    if (!dev->gd) {
        printk (KERN_NOTICE "alloc_disk failure\n");
        return -ENOMEM;
    }

    dev->gd->major = 1;
    dev->gd->first_minor = 0;
    dev->gd->fops = &sbull_ops;         
    dev->gd->queue = dev->queue;
    dev->gd->private_data = dev;
    snprintf (dev->gd->disk_name, 32, "myblock");
    set_capacity(dev->gd, NR_SECTORS);

    add_disk(dev->gd);

    return 0;
}

int hello_module(void){
    int status = register_blkdev(240, "MY_BLKDEV_NAME");
    printk(KERN_INFO "Hello world 1.\n");


    if (status < 0) {
        printk(KERN_ERR "unable to register mybdev block device\n");
        return -5;
    }

    //create_block_device(&dev);

    printk(KERN_INFO "Device Registered...checking status.\n");
    status = create_block_device(&dev);
    if (status < 0)
        return status;

    /*          
     * A non 0 return means init_module failed; module can't be loaded.          
     */
    return 0;
}


static void delete_block_device(struct block_dev *dev){
    if (dev->gd) {
        del_gendisk(dev->gd);
    }


}


void bye_module(void){
    printk(KERN_INFO "Goodbye world 1.\n");
    delete_block_device(&dev);
    unregister_blkdev(240, "MY_BLKDEV_NAME");
    printk(KERN_INFO "Deleted & unregistered.\n");
}

module_init(hello_module);
module_exit(bye_module);

/* This is a Linux Block Driver which simulates a block device with a region of memory
 * init, exit, and IO/IOCTL functionality must be included.
 */
