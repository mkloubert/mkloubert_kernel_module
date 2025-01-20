/**
 * @file mkloubert.c
 * @brief A simple dynamically loadable Linux kernel module that creates a proc file entry.
 *
 * This module creates a /proc entry named "mkloubert_driver" and provides a read handler
 * to output a simple "Ack!\n" message when the proc entry is read.
 */

#include <linux/init.h>    // For module initialization macros
#include <linux/module.h>  // For module macros
#include <linux/proc_fs.h> // For proc filesystem operations
#include <linux/uaccess.h> // For copy_to_user function

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Marcel Joachim Kloubert");
MODULE_DESCRIPTION("A blueprint for a dynamically loadable kernel module");

/**
 * @brief Pointer to the proc entry created by this module.
 */
static struct proc_dir_entry *custom_proc_node;

/**
 * @brief Read handler for the proc file.
 *
 * This function is called when the /proc/mkloubert_driver file is read.
 * It outputs a simple "Hail to The GitFather!\n" message.
 *
 * @param file_pointer Pointer to the file structure (unused).
 * @param user_space_buffer Buffer in user space to write the data.
 * @param count Number of bytes requested (ignored, as we always write the entire message).
 * @param offset Pointer to the current read offset.
 * @return Number of bytes written, or 0 if the end of the message is reached.
 */
static ssize_t mkloubert_read(
    struct file *file_pointer,
    char *user_space_buffer,
    size_t count,
    loff_t *offset)
{
    const char msg[] = "Hail to The GitFather!\n";
    size_t len = strlen(msg);

    // check if the offset indicates end of the message
    if (*offset >= len)
    {
        return 0; // EOF (End Of File)
    }

    // Copy message to user space
    if (copy_to_user(user_space_buffer, msg, len) != 0)
    {
        return -EFAULT; // failed
    }

    // update offset and return the number of bytes written
    *offset += len;
    return len;
}

/**
 * @brief Operations structure for the proc file.
 */
static struct proc_ops driver_proc_ops = {
    .proc_read = mkloubert_read,
};

/**
 * @brief Module initialization function.
 *
 * This function is called when the module is loaded into the kernel. It creates
 * a proc entry named "mkloubert_driver" and assigns the read handler.
 *
 * @return 0 on success, -1 on failure.
 */
static int __init mkloubert_module_init(void)
{
    // Create a proc entry
    custom_proc_node = proc_create(
        "mkloubert",     // Name of the proc entry (/proc/mkloubert)
        0,               // Permissions
        NULL,            // Parent directory (NULL for /proc)
        &driver_proc_ops // Operations structure
    );

    if (custom_proc_node == NULL)
    {
        printk(KERN_ERR "mkloubert_module_init: Failed to create proc entry\n");
        return -ENOMEM; // Return memory allocation error
    }

    printk(KERN_INFO "mkloubert_module_init: Proc entry created successfully\n");
    return 0;
}

/**
 * @brief Module cleanup function.
 *
 * This function is called when the module is removed from the kernel. It removes
 * the proc entry created during initialization.
 */
static void __exit mkloubert_module_exit(void)
{
    // remove the proc entry
    proc_remove(custom_proc_node);
    printk(KERN_INFO "mkloubert_module_exit: Proc entry removed\n");
}

module_init(mkloubert_module_init);
module_exit(mkloubert_module_exit);
