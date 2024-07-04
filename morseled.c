#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/semaphore.h> 
#include<linux/delay.h>
#include <linux/init.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "morse_capslock"
#define MORSE_DOT_DELAY_SEC 1    // Delay for a dot in seconds
#define MORSE_DASH_DELAY_SEC 3   // Delay for a dash in seconds
#define MORSE_CHAR_DELAY_SEC 3   // Delay between characters in seconds
#define MORSE_WORD_DELAY_SEC 7   // Delay between words in seconds

MODULE_AUTHOR("sem4-2024");
MODULE_DESCRIPTION("Kernel module for displaying Morse code using Caps Lock LED");
MODULE_LICENSE("GPL");

static struct semaphore morse_sem;


static void display_morse(const char *str)
{
    struct file *filehandle;
    loff_t pos = 0;
    clock_t start_time, end_time;

    // Open the Caps Lock LED brightness file
    filehandle = filp_open("/sys/class/leds/input2::capslock/brightness", O_WRONLY, 0);
    if (IS_ERR(filehandle)) {
        printk(KERN_ERR "Failed to open Caps Lock LED brightness file.\n");
        return;
    }

    while (*str != '\0') {
        switch (*str) {
                        case 'a':
            case 'A':
                // Display dot-dash for 'A' (.-)
                kernel_write(filehandle, "1", 1, &pos); // Turn on LED for dot
                msleep(MORSE_DOT_DELAY_SEC * 1000); // Delay for dot duration
                kernel_write(filehandle, "0", 1, &pos); // Turn off LED
                msleep(MORSE_DOT_DELAY_SEC * 1000); // Delay between dot and dash
                kernel_write(filehandle, "1", 1, &pos); // Turn on LED for dash
                msleep(MORSE_DASH_DELAY_SEC * 1000); // Delay for dash duration
                kernel_write(filehandle, "0", 1, &pos); // Turn off LED
                break;

            case 'b':
            case 'B':
                // Display dash-three-dots for 'B' (-...)
                kernel_write(filehandle, "1", 1, &pos); // Turn on LED for dash
                msleep(MORSE_DASH_DELAY_SEC * 1000); // Delay for dash duration
                kernel_write(filehandle, "0", 1, &pos); // Turn off LED
                // Three dots
                for (int i = 0; i < 3; i++) {
                    kernel_write(filehandle, "1", 1, &pos); // Turn on LED for dot
                    msleep(MORSE_DOT_DELAY_SEC * 1000); // Delay for dot duration
                    kernel_write(filehandle, "0", 1, &pos); // Turn off LED
                    msleep(MORSE_DOT_DELAY_SEC * 1000); // Delay between dot and dot
                }
                break;

            case 'c':
            case 'C':
                // Display dash-dot-dash-dot for 'C' (-.-.)
                kernel_write(filehandle, "1", 1, &pos); // Turn on LED for dash
                msleep(MORSE_DASH_DELAY_SEC * 1000); // Delay for dash duration
                kernel_write(filehandle, "0", 1, &pos); // Turn off LED
                msleep(MORSE_DOT_DELAY_SEC * 1000); // Delay between dash and dot
                kernel_write(filehandle, "1", 1, &pos); // Turn on LED for dot
                msleep(MORSE_DOT_DELAY_SEC * 1000); // Delay for dot duration
                kernel_write(filehandle, "0", 1, &pos); // Turn off LED
                msleep(MORSE_DOT_DELAY_SEC * 1000); // Delay between dots
                kernel_write(filehandle, "1", 1, &pos); // Turn on LED for dash
                msleep(MORSE_DASH_DELAY_SEC * 1000); // Delay for dash duration
                kernel_write(filehandle, "0", 1, &pos); // Turn off LED
                msleep(MORSE_DOT_DELAY_SEC * 1000); // Delay between dash and dot
                kernel_write(filehandle, "1", 1, &pos); // Turn on LED for dot
                msleep(MORSE_DOT_DELAY_SEC * 1000); // Delay for dot duration
                kernel_write(filehandle, "0", 1, &pos); // Turn off LED
                break;

            case 'd':
            case 'D':
                // Display dash-dot-dot for 'D' (-..)
                kernel_write(filehandle, "1", 1, &pos); // Turn on LED for dash
                msleep(MORSE_DASH_DELAY_SEC * 1000); // Delay for dash duration
                kernel_write(filehandle, "0", 1, &pos); // Turn off LED
                msleep(MORSE_DOT_DELAY_SEC * 1000); // Delay between dash and dot
                kernel_write(filehandle, "1", 1, &pos); // Turn on LED for dot
                msleep(MORSE_DOT_DELAY_SEC * 1000); // Delay for dot duration
                kernel_write(filehandle, "0", 1, &pos); // Turn off LED
                msleep(MORSE_DOT_DELAY_SEC * 1000); // Delay between dots
                kernel_write(filehandle, "1", 1, &pos); // Turn on LED for dot
                msleep(MORSE_DOT_DELAY_SEC * 1000); // Delay for dot duration
                kernel_write(filehandle, "0", 1, &pos); // Turn off LED
                break;

            case 'e':
            case 'E':
                // Display dot for 'E' (.)
                kernel_write(filehandle, "1", 1, &pos); 
                msleep(MORSE_DOT_DELAY_SEC * 1000); 
                kernel_write(filehandle, "0", 1, &pos); 
                break;

            case 'f':
            case 'F':
                // Display dot-dot-dash for 'F' (..-)
                kernel_write(filehandle, "1", 1, &pos); 
                msleep(MORSE_DOT_DELAY_SEC * 1000); 
                kernel_write(filehandle, "0", 1, &pos); 
                msleep(MORSE_DOT_DELAY_SEC * 1000); 
                kernel_write(filehandle, "1", 1, &pos); 
                msleep(MORSE_DOT_DELAY_SEC * 1000); 
                kernel_write(filehandle, "0", 1, &pos); 
                msleep(MORSE_DOT_DELAY_SEC * 1000); 
                kernel_write(filehandle, "1", 1, &pos); 
                msleep(MORSE_DASH_DELAY_SEC * 1000); 
                kernel_write(filehandle, "0", 1, &pos); 
                break;    

    case 'g':
    case 'G':
        // Display dash-dash-dot for 'G' (--.)
        kernel_write(filehandle, "1", 1, &pos); 
        msleep(MORSE_DASH_DELAY_SEC * 1000); 
        kernel_write(filehandle, "0", 1, &pos); 
        msleep(MORSE_DOT_DELAY_SEC * 1000); 
        kernel_write(filehandle, "1", 1, &pos); 
        msleep(MORSE_DASH_DELAY_SEC * 1000); 
        kernel_write(filehandle, "0", 1, &pos); 
        msleep(MORSE_DOT_DELAY_SEC * 1000); 
        kernel_write(filehandle, "1", 1, &pos); 
        msleep(MORSE_DOT_DELAY_SEC * 1000); 
        kernel_write(filehandle, "0", 1, &pos); 
        break;

    case 'h':
    case 'H':
        // Display four dots for 'H' (....)
        for (int i = 0; i < 4; i++) {
            kernel_write(filehandle, "1", 1, &pos); 
            msleep(MORSE_DOT_DELAY_SEC * 1000); 
            kernel_write(filehandle, "0", 1, &pos); 
            msleep(MORSE_DOT_DELAY_SEC * 1000); 
        }
        break;

    case 'i':
    case 'I':
        // Display two dots for 'I' (..)
        for (int i = 0; i < 2; i++) {
            kernel_write(filehandle, "1", 1, &pos); 
            msleep(MORSE_DOT_DELAY_SEC * 1000); 
            kernel_write(filehandle, "0", 1, &pos); 
            msleep(MORSE_DOT_DELAY_SEC * 1000); 
        }
        break;

    case 'j':
    case 'J':
        // Display dot-dash-dash-dash for 'J' (.---)
        kernel_write(filehandle, "1", 1, &pos); 
        msleep(MORSE_DOT_DELAY_SEC * 1000); 
        kernel_write(filehandle, "0", 1, &pos); 
        msleep(MORSE_DOT_DELAY_SEC * 1000);  and dash
        kernel_write(filehandle, "1", 1, &pos); 
        msleep(MORSE_DASH_DELAY_SEC * 1000); 
        kernel_write(filehandle, "0", 1, &pos); 
        msleep(MORSE_DOT_DELAY_SEC * 1000); 
        kernel_write(filehandle, "1", 1, &pos); 
        msleep(MORSE_DASH_DELAY_SEC * 1000); 
        kernel_write(filehandle, "0", 1, &pos); 
        msleep(MORSE_DOT_DELAY_SEC * 1000);  and dot
        kernel_write(filehandle, "1", 1, &pos); 
        msleep(MORSE_DASH_DELAY_SEC * 1000); 
        kernel_write(filehandle, "0", 1, &pos); 
        break;

    case 'k':
    case 'K':
        // Display dash-dot-dash for 'K' (-.-)
        kernel_write(filehandle, "1", 1, &pos); 
        msleep(MORSE_DASH_DELAY_SEC * 1000); 
        kernel_write(filehandle, "0", 1, &pos); 
        msleep(MORSE_DOT_DELAY_SEC * 1000);
        kernel_write(filehandle, "1", 1, &pos); 
        msleep(MORSE_DOT_DELAY_SEC * 1000); 
        kernel_write(filehandle, "0", 1, &pos); 
        msleep(MORSE_DOT_DELAY_SEC * 1000); 
        kernel_write(filehandle, "1", 1, &pos); 
        msleep(MORSE_DASH_DELAY_SEC * 1000); 
        kernel_write(filehandle, "0", 1, &pos); 
        break;

    case 'l':
    case 'L':
        // Display dot-dash-dot-dot for 'L' (.-..)
        kernel_write(filehandle, "1", 1, &pos); 
        msleep(MORSE_DOT_DELAY_SEC * 1000); 
        kernel_write(filehandle, "0", 1, &pos); 
        msleep(MORSE_DOT_DELAY_SEC * 1000); 
        kernel_write(filehandle, "1", 1, &pos); 
        msleep(MORSE_DASH_DELAY_SEC * 1000); 
        kernel_write(filehandle, "0", 1, &pos); 
        msleep(MORSE_DOT_DELAY_SEC * 1000); 
        kernel_write(filehandle, "1", 1, &pos); 
        msleep(MORSE_DOT_DELAY_SEC * 1000); 
        kernel_write(filehandle, "0", 1, &pos); 
        msleep(MORSE_DOT_DELAY_SEC * 1000); 
        kernel_write(filehandle, "1", 1, &pos); 
        msleep(MORSE_DOT_DELAY_SEC * 1000); 
        kernel_write(filehandle, "0", 1, &pos); 
        break;

    case 'm':
    case 'M':
        // Display dash-dash for 'M' (--)
        kernel_write(filehandle, "1", 1, &pos); 
        msleep(MORSE_DASH_DELAY_SEC * 1000); 
        kernel_write(filehandle, "0", 1, &pos); 
        msleep(MORSE_DOT_DELAY_SEC * 1000); 
        kernel_write(filehandle, "1", 1, &pos); 
        msleep(MORSE_DASH_DELAY_SEC * 1000); 
        kernel_write(filehandle, "0", 1, &pos); 
        break;

    case 'n':
    case 'N':
        // Display dash-dot for 'N' (-.)
        kernel_write(filehandle, "1", 1, &pos); 
        msleep(MORSE_DASH_DELAY_SEC * 1000); 
        kernel_write(filehandle, "0", 1, &pos); 
        msleep(MORSE_DOT_DELAY_SEC * 1000); 
        kernel_write(filehandle, "1", 1, &pos); 
        msleep(MORSE_DOT_DELAY_SEC * 1000); 
        kernel_write(filehandle, "0", 1, &pos); 
        break;

    case 'o':
    case 'O':
        // Display dash-dash-dash for 'O' (---)
        for (int i = 0; i < 3; i++) {
            kernel_write(filehandle, "1", 1, &pos); 
            msleep(MORSE_DASH_DELAY_SEC * 1000); 
            kernel_write(filehandle, "0", 1, &pos); 
            msleep(MORSE_DOT_DELAY_SEC * 1000); 
        }
        break;

    case 'p':
    case 'P':
        // Display dot-dash-dash-dot for 'P' (.--.)
        kernel_write(filehandle, "1", 1, &pos); 
        msleep(MORSE_DOT_DELAY_SEC * 1000); 
        kernel_write(filehandle, "0", 1, &pos); 
        msleep(MORSE_DOT_DELAY_SEC * 1000);  and dash
        kernel_write(filehandle, "1", 1, &pos); 
        msleep(MORSE_DASH_DELAY_SEC * 1000); 
        kernel_write(filehandle, "0", 1, &pos); 
        msleep(MORSE_DASH_DELAY_SEC * 1000);
        kernel_write(filehandle, "1", 1, &pos); 
        msleep(MORSE_DASH_DELAY_SEC * 1000); 
        kernel_write(filehandle, "0", 1, &pos); 
        msleep(MORSE_DOT_DELAY_SEC * 1000);  and dot
        kernel_write(filehandle, "1", 1, &pos); 
        msleep(MORSE_DOT_DELAY_SEC * 1000); 
        kernel_write(filehandle, "0", 1, &pos); 
        break;

    case 'q':
    case 'Q':
        // Display dash-dash-dot-dash for 'Q' (--.-)
        kernel_write(filehandle, "1", 1, &pos); 
        msleep(MORSE_DASH_DELAY_SEC * 1000); 
        kernel_write(filehandle, "0", 1, &pos); 
        msleep(MORSE_DASH_DELAY_SEC * 1000);  and dots
        kernel_write(filehandle, "1", 1, &pos); 
        msleep(MORSE_DASH_DELAY_SEC * 1000); 
        kernel_write(filehandle, "0", 1, &pos); 
        msleep(MORSE_DOT_DELAY_SEC * 1000);  and dash
        kernel_write(filehandle, "1", 1, &pos); 
        msleep(MORSE_DOT_DELAY_SEC * 1000); 
        kernel_write(filehandle, "0", 1, &pos); 
        msleep(MORSE_DASH_DELAY_SEC * 1000);
        kernel_write(filehandle, "1", 1, &pos); 
        msleep(MORSE_DASH_DELAY_SEC * 1000); 
        kernel_write(filehandle, "0", 1, &pos); 
        break;

    case 'r':
    case 'R':
        // Display dot-dash-dot for 'R' (.-.)
        kernel_write(filehandle, "1", 1, &pos); 
        msleep(MORSE_DOT_DELAY_SEC * 1000); 
        kernel_write(filehandle, "0", 1, &pos); 
        msleep(MORSE_DOT_DELAY_SEC * 1000);  and dash
        kernel_write(filehandle, "1", 1, &pos); 
        msleep(MORSE_DASH_DELAY_SEC * 1000); 
        kernel_write(filehandle, "0", 1, &pos); 
        msleep(MORSE_DOT_DELAY_SEC * 1000); 
        kernel_write(filehandle, "1", 1, &pos); 
        msleep(MORSE_DOT_DELAY_SEC * 1000); 
        kernel_write(filehandle, "0", 1, &pos); 
        break;

    case 's':
    case 'S':
        // Display dot-dot-dot for 'S' (...)
        for (int i = 0; i < 3; i++) {
            kernel_write(filehandle, "1", 1, &pos); 
            msleep(MORSE_DOT_DELAY_SEC * 1000); 
            kernel_write(filehandle, "0", 1, &pos); 
            msleep(MORSE_DOT_DELAY_SEC * 1000); 
        }
        break;

    case 't':
    case 'T':
        // Display dash for 'T' (-)
        kernel_write(filehandle, "1", 1, &pos); 
        msleep(MORSE_DASH_DELAY_SEC * 1000); 
        kernel_write(filehandle, "0", 1, &pos); 
        break;

    case 'u':
    case 'U':
        // Display dot-dot-dash for 'U' (..-)
        kernel_write(filehandle, "1", 1, &pos); 
        msleep(MORSE_DOT_DELAY_SEC * 1000); 
        kernel_write(filehandle, "0", 1, &pos); 
        msleep(MORSE_DOT_DELAY_SEC * 1000); 
        kernel_write(filehandle, "1", 1, &pos); 
        msleep(MORSE_DOT_DELAY_SEC * 1000); 
        kernel_write(filehandle, "0", 1, &pos); 
        msleep(MORSE_DASH_DELAY_SEC * 1000); 
        kernel_write(filehandle, "1", 1, &pos); 
        msleep(MORSE_DASH_DELAY_SEC * 1000); 
        kernel_write(filehandle, "0", 1, &pos); 
        break;

    case 'v':
    case 'V':
        // Display dot-dot-dot-dash for 'V' (...-)
        for (int i = 0; i < 3; i++) {
            kernel_write(filehandle, "1", 1, &pos); 
            msleep(MORSE_DOT_DELAY_SEC * 1000); 
            kernel_write(filehandle, "0", 1, &pos); 
            msleep(MORSE_DOT_DELAY_SEC * 1000); 
        }
        kernel_write(filehandle, "1", 1, &pos); 
        msleep(MORSE_DASH_DELAY_SEC * 1000); 
        kernel_write(filehandle, "0", 1, &pos); 
        break;

    case 'w':
    case 'W':
        // Display dot-dash-dash for 'W' (.--)
        kernel_write(filehandle, "1", 1, &pos); 
        msleep(MORSE_DOT_DELAY_SEC * 1000); 
        kernel_write(filehandle, "0", 1, &pos); 
        msleep(MORSE_DOT_DELAY_SEC * 1000); 
        kernel_write(filehandle, "1", 1, &pos); 
        msleep(MORSE_DASH_DELAY_SEC * 1000); 
        kernel_write(filehandle, "0", 1, &pos); 
        msleep(MORSE_DOT_DELAY_SEC * 1000); 
        kernel_write(filehandle, "1", 1, &pos); 
        msleep(MORSE_DASH_DELAY_SEC * 1000); 
        kernel_write(filehandle, "0", 1, &pos); 
        break;

    case 'x':
    case 'X':
        // Display dash-dot-dot-dash for 'X' (-..-)
        kernel_write(filehandle, "1", 1, &pos); 
        msleep(MORSE_DASH_DELAY_SEC * 1000); 
        kernel_write(filehandle, "0", 1, &pos); 
        msleep(MORSE_DOT_DELAY_SEC * 1000);
        kernel_write(filehandle, "1", 1, &pos); 
        msleep(MORSE_DOT_DELAY_SEC * 1000); 
        kernel_write(filehandle, "0", 1, &pos); 
        msleep(MORSE_DOT_DELAY_SEC * 1000); 
        kernel_write(filehandle, "1", 1, &pos); 
        msleep(MORSE_DOT_DELAY_SEC * 1000); 
        kernel_write(filehandle, "0", 1, &pos); 
        msleep(MORSE_DASH_DELAY_SEC * 1000);  
        kernel_write(filehandle, "1", 1, &pos); 
        msleep(MORSE_DASH_DELAY_SEC * 1000); 
        kernel_write(filehandle, "0", 1, &pos); 
        break;

    case 'y':
    case 'Y':
        // Display dash-dot-dash-dash for 'Y' (-.--)
        kernel_write(filehandle, "1", 1, &pos); 
        msleep(MORSE_DASH_DELAY_SEC * 1000); 
        kernel_write(filehandle, "0", 1, &pos); 
        msleep(MORSE_DOT_DELAY_SEC * 1000); 
        kernel_write(filehandle, "1", 1, &pos); 
        msleep(MORSE_DOT_DELAY_SEC * 1000); 
        kernel_write(filehandle, "0", 1, &pos); 
        msleep(MORSE_DASH_DELAY_SEC * 1000);  
        kernel_write(filehandle, "1", 1, &pos); 
        msleep(MORSE_DASH_DELAY_SEC * 1000); 
        kernel_write(filehandle, "0", 1, &pos); 
        msleep(MORSE_DASH_DELAY_SEC * 1000); 
        kernel_write(filehandle, "1", 1, &pos); 
        msleep(MORSE_DASH_DELAY_SEC * 1000); 
        kernel_write(filehandle, "0", 1, &pos); 
        break;

    case 'z':
    case 'Z':
        // Display dash-dash-dot-dot for 'Z' (--..)
        kernel_write(filehandle, "1", 1, &pos); 
        msleep(MORSE_DASH_DELAY_SEC * 1000); 
        kernel_write(filehandle, "0", 1, &pos); 
        msleep(MORSE_DASH_DELAY_SEC * 1000);  
        kernel_write(filehandle, "1", 1, &pos); 
        msleep(MORSE_DASH_DELAY_SEC * 1000); 
        kernel_write(filehandle, "0", 1, &pos); 
        msleep(MORSE_DOT_DELAY_SEC * 1000);  
        kernel_write(filehandle, "1", 1, &pos); 
        msleep(MORSE_DOT_DELAY_SEC * 1000); 
        kernel_write(filehandle, "0", 1, &pos); 
        msleep(MORSE_DOT_DELAY_SEC * 1000); 
        kernel_write(filehandle, "1", 1, &pos); 
        msleep(MORSE_DOT_DELAY_SEC * 1000); 
        kernel_write(filehandle, "0", 1, &pos); 
        break;

            default:

                break;
        }

        str++;

        msleep(MORSE_CHAR_DELAY_SEC * 1000);
    }

    filp_close(filehandle, NULL);
}

static ssize_t morse_write(struct file *file, const char __user *buf,
                           size_t count, loff_t *ppos)
{
    char input_buffer[256]; 
    ssize_t ret;

    if (count >= sizeof(input_buffer))
        count=255;

    if (down_interruptible(&morse_sem)) //acquire semaphore
        return -ERESTARTSYS;

    ret = copy_from_user(input_buffer, buf, count);
    if (ret)
        up(&morse_sem)  //releasing semaphore
        return -EFAULT;

    input_buffer[count] = '\0';

    display_morse(input_buffer); 
    up(&morse_sem);//releasing semaphore

    return count;
}

static const struct file_operations morse_fops = {
    .owner = THIS_MODULE,
    .write = morse_write,
};

static int __init morse_init(void)
{
    int ret;

    sema_init(&morse_sem, 1);
    ret = register_chrdev(0, DEVICE_NAME, &morse_fops);
    if (ret < 0) {
        printk(KERN_ALERT "Failed to register a device.\n");
        return ret;
    }

    printk(KERN_INFO "Morse code display module has been loaded.\n");
    printk(KERN_INFO "I was assigned major number %d. To talk to\n", ret);
    printk(KERN_INFO "the driver, create a dev file with\n");
    printk(KERN_INFO "'mknod /dev/%s c %d 0'.\n", DEVICE_NAME, ret);

    return 0;
}

static void __exit morse_exit(void)
{

    unregister_chrdev(0, DEVICE_NAME);
    printk(KERN_INFO "Morse code display module has been unloaded.\n");
}

module_init(morse_init);
module_exit(morse_exit);
