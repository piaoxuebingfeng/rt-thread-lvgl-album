/**
 * @file lv_port_fs_templ.c
 *
 */

 /*Copy this file as "lv_port_fs.c" and set this value to "1" to enable content*/
#if 1

/*********************
 *      INCLUDES
 *********************/
#include "lv_port_fs.h"
#include "lvgl.h"

 #if USE_DFS_SYSTEM==1
 
#include "dfs.h"
#include "fcntl.h"
#include "unistd.h"

#endif

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void fs_init(void);
#if USE_FATFS_FILE_SYSTEM==1
static void * fs_open(lv_fs_drv_t * drv, const char * path, lv_fs_mode_t mode);
static lv_fs_res_t fs_close(lv_fs_drv_t * drv, void * file_p);
static lv_fs_res_t fs_read(lv_fs_drv_t * drv, void * file_p, void * buf, uint32_t btr, uint32_t * br);
static lv_fs_res_t fs_write(lv_fs_drv_t * drv, void * file_p, const void * buf, uint32_t btw, uint32_t * bw);
static lv_fs_res_t fs_seek(lv_fs_drv_t * drv, void * file_p, uint32_t pos, lv_fs_whence_t whence);
static lv_fs_res_t fs_size(lv_fs_drv_t * drv, void * file_p, uint32_t * size_p);
static lv_fs_res_t fs_tell(lv_fs_drv_t * drv, void * file_p, uint32_t * pos_p);

static void * fs_dir_open(lv_fs_drv_t * drv, const char *path);
static lv_fs_res_t fs_dir_read(lv_fs_drv_t * drv, void * rddir_p, char * fn);
static lv_fs_res_t fs_dir_close(lv_fs_drv_t * drv, void * rddir_p);
#endif


/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
 // 使用 rtthread 提供的 dfs
 #if USE_DFS_SYSTEM==1
bool dfs_ready(lv_fs_drv_t *drv);
static void* dfs_open(lv_fs_drv_t *drv, const char *fn, lv_fs_mode_t mode);
static lv_fs_res_t dfs_write(struct _lv_fs_drv_t *drv, void *file_p,
		const void *buf, uint32_t btw, uint32_t *bw);
static lv_fs_res_t dfs_read(lv_fs_drv_t *drv, void *file_p, void *buf,
		uint32_t btr, uint32_t *br);
static lv_fs_res_t dfs_close(lv_fs_drv_t *drv, void *file_p);
static lv_fs_res_t dfs_seek(lv_fs_drv_t *drv, void *file_p, uint32_t pos,
		lv_fs_whence_t whence);
static lv_fs_res_t dfs_tell(lv_fs_drv_t *drv, void *file_p, uint32_t *pos_p);


// 参考 lv_fs_posix.c 实现
//static void * dfs_dir_open(lv_fs_drv_t * drv, const char * path);
//static lv_fs_res_t dfs_dir_read(lv_fs_drv_t * drv, void * dir_p, char * fn);
//static lv_fs_res_t dfs_dir_close(lv_fs_drv_t * drv, void * dir_p);
 
 #endif
 

void lv_port_fs_init(void)
{
    /*----------------------------------------------------
     * Initialize your storage device and File System
     * -------------------------------------------------*/
    fs_init();

    /*---------------------------------------------------
     * Register the file system interface in LVGL
     *--------------------------------------------------*/
#if USE_FATFS_FILE_SYSTEM==1
    /*Add a simple drive to open images*/
    static lv_fs_drv_t fs_drv;
    lv_fs_drv_init(&fs_drv);

    /*Set up fields...*/
    fs_drv.letter = 'P';
    fs_drv.open_cb = fs_open;
    fs_drv.close_cb = fs_close;
    fs_drv.read_cb = fs_read;
    fs_drv.write_cb = fs_write;
    fs_drv.seek_cb = fs_seek;
    fs_drv.tell_cb = fs_tell;

    fs_drv.dir_close_cb = fs_dir_close;
    fs_drv.dir_open_cb = fs_dir_open;
    fs_drv.dir_read_cb = fs_dir_read;

    lv_fs_drv_register(&fs_drv);
#endif

#if USE_DFS_SYSTEM==1

	static lv_fs_drv_t dfs_drv; /*A driver descriptor*/
	lv_fs_drv_init(&dfs_drv);
	dfs_drv.user_data = NULL;
	dfs_drv.letter = 'S';
	dfs_drv.ready_cb = dfs_ready;
	dfs_drv.write_cb = dfs_write;
	dfs_drv.open_cb = dfs_open;
	dfs_drv.close_cb = dfs_close;
	dfs_drv.read_cb = dfs_read;
	dfs_drv.seek_cb = dfs_seek;
	dfs_drv.tell_cb = dfs_tell;
	
//	dfs_drv.dir_close_cb= dfs_dir_close;
//	dfs_drv.dir_open_cb = dfs_dir_open;
//	dfs_drv.dir_read_cb = dfs_dir_read;

	lv_fs_drv_register(&dfs_drv);
#endif
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/*Initialize your Storage device and File system.*/
static void fs_init(void)
{
    /*E.g. for FatFS initialize the SD card and FatFS itself*/

    /*You code here*/
}



#if USE_DFS_SYSTEM==1

// 下面的方法要基于 dfs 来一一实现

bool dfs_ready(lv_fs_drv_t *drv) {
	(void) drv; /*Unused*/
	
	return true;  //这里仅返回true,如果是嵌入式，则是返回嵌入式文件系统挂载成功与否的标志
}


static void* dfs_open(lv_fs_drv_t *drv, const char *fn, lv_fs_mode_t mode) {
	(void) drv; /*Unused*/
	

	int flags =0;
	if (mode == LV_FS_MODE_WR)
		flags = O_WRONLY ;
	else if (mode == LV_FS_MODE_RD)
		flags = O_RDONLY;
	else if (mode == (LV_FS_MODE_WR | LV_FS_MODE_RD))
		flags = O_RDWR;
	
    /*Make the path relative to the current directory (the projects root folder)*/
    char buf[256];
//    sprintf(buf, LV_FS_POSIX_PATH "%s", path);
		sprintf(buf, "%s", fn);
//		rt_kprintf("file path is %s \r\n",buf);
		
    int f = open(buf, flags);
    if(f < 0) 
		{
			rt_kprintf("%s file is not found\r\n",buf);
			return NULL;
		}
    return (void *)(lv_uintptr_t)f;
}


//写入文件被回调的函数 dfs_write
static lv_fs_res_t dfs_write(struct _lv_fs_drv_t *drv, void *file_p,
		const void *buf, uint32_t btw, uint32_t *bw) {
			
			
	(void) drv; /*Unused*/
			
	*bw = write((lv_uintptr_t)file_p, buf, btw);
	return (int32_t)(*bw) < 0 ? LV_FS_RES_UNKNOWN : LV_FS_RES_OK;
}

//读取文件被回调的函数 dfs_read
static lv_fs_res_t dfs_read(lv_fs_drv_t *drv, void *file_p, void *buf,
		uint32_t btr, uint32_t *br) {
	(void) drv; /*Unused*/

	*br = read((lv_uintptr_t)file_p, buf, btr);
	return (int32_t)(*br) < 0 ? LV_FS_RES_UNKNOWN : LV_FS_RES_OK;

}
		
//关闭文件被回调的函数 dfs_close
static lv_fs_res_t dfs_close(lv_fs_drv_t *drv, void *file_p) {
	(void) drv; /*Unused*/
	close((lv_uintptr_t)file_p);
	return LV_FS_RES_OK;
	//return fclose(file_p);
}
		
//移动文件位置被回调的函数 dfs_seek
static lv_fs_res_t dfs_seek(lv_fs_drv_t *drv, void *file_p, uint32_t pos,
		lv_fs_whence_t whence) {
	(void) drv; /*Unused*/

	lseek((lv_uintptr_t)file_p, pos, whence);
	return LV_FS_RES_OK;
}
		
//获取文件位置被回调的函数 dfs_tell
static lv_fs_res_t dfs_tell(lv_fs_drv_t *drv, void *file_p, uint32_t *pos_p) {
	(void) drv; /*Unused*/
	
    *pos_p = lseek((lv_uintptr_t)file_p, 0, SEEK_CUR);
    return LV_FS_RES_OK;
}


//static void * dfs_dir_open(lv_fs_drv_t * drv, const char * path)
//{
//	
//}
//static lv_fs_res_t dfs_dir_read(lv_fs_drv_t * drv, void * dir_p, char * fn)
//{
//	
//}
//static lv_fs_res_t dfs_dir_close(lv_fs_drv_t * drv, void * dir_p)
//{
//	
//}	


#endif



#if USE_FATFS_FILE_SYSTEM==1
/**
 * Open a file
 * @param drv       pointer to a driver where this function belongs
 * @param path      path to the file beginning with the driver letter (e.g. S:/folder/file.txt)
 * @param mode      read: FS_MODE_RD, write: FS_MODE_WR, both: FS_MODE_RD | FS_MODE_WR
 * @return          a file descriptor or NULL on error
 */
static void * fs_open(lv_fs_drv_t * drv, const char * path, lv_fs_mode_t mode)
{
    lv_fs_res_t res = LV_FS_RES_NOT_IMP;

    void * f = NULL;

    if(mode == LV_FS_MODE_WR)
    {
        /*Open a file for write*/
        f = ...         /*Add your code here*/
    }
    else if(mode == LV_FS_MODE_RD)
    {
        /*Open a file for read*/
        f = ...         /*Add your code here*/
    }
    else if(mode == (LV_FS_MODE_WR | LV_FS_MODE_RD))
    {
        /*Open a file for read and write*/
        f = ...         /*Add your code here*/
    }

    return f;
}

/**
 * Close an opened file
 * @param drv       pointer to a driver where this function belongs
 * @param file_p    pointer to a file_t variable. (opened with fs_open)
 * @return          LV_FS_RES_OK: no error or  any error from @lv_fs_res_t enum
 */
static lv_fs_res_t fs_close(lv_fs_drv_t * drv, void * file_p)
{
    lv_fs_res_t res = LV_FS_RES_NOT_IMP;

    /*Add your code here*/

    return res;
}

/**
 * Read data from an opened file
 * @param drv       pointer to a driver where this function belongs
 * @param file_p    pointer to a file_t variable.
 * @param buf       pointer to a memory block where to store the read data
 * @param btr       number of Bytes To Read
 * @param br        the real number of read bytes (Byte Read)
 * @return          LV_FS_RES_OK: no error or  any error from @lv_fs_res_t enum
 */
static lv_fs_res_t fs_read(lv_fs_drv_t * drv, void * file_p, void * buf, uint32_t btr, uint32_t * br)
{
    lv_fs_res_t res = LV_FS_RES_NOT_IMP;

    /*Add your code here*/

    return res;
}

/**
 * Write into a file
 * @param drv       pointer to a driver where this function belongs
 * @param file_p    pointer to a file_t variable
 * @param buf       pointer to a buffer with the bytes to write
 * @param btr       Bytes To Write
 * @param br        the number of real written bytes (Bytes Written). NULL if unused.
 * @return          LV_FS_RES_OK: no error or  any error from @lv_fs_res_t enum
 */
static lv_fs_res_t fs_write(lv_fs_drv_t * drv, void * file_p, const void * buf, uint32_t btw, uint32_t * bw)
{
    lv_fs_res_t res = LV_FS_RES_NOT_IMP;

    /*Add your code here*/

    return res;
}

/**
 * Set the read write pointer. Also expand the file size if necessary.
 * @param drv       pointer to a driver where this function belongs
 * @param file_p    pointer to a file_t variable. (opened with fs_open )
 * @param pos       the new position of read write pointer
 * @param whence    tells from where to interpret the `pos`. See @lv_fs_whence_t
 * @return          LV_FS_RES_OK: no error or  any error from @lv_fs_res_t enum
 */
static lv_fs_res_t fs_seek(lv_fs_drv_t * drv, void * file_p, uint32_t pos, lv_fs_whence_t whence)
{
    lv_fs_res_t res = LV_FS_RES_NOT_IMP;

    /*Add your code here*/

    return res;
}
/**
 * Give the position of the read write pointer
 * @param drv       pointer to a driver where this function belongs
 * @param file_p    pointer to a file_t variable.
 * @param pos_p     pointer to to store the result
 * @return          LV_FS_RES_OK: no error or  any error from @lv_fs_res_t enum
 */
static lv_fs_res_t fs_tell(lv_fs_drv_t * drv, void * file_p, uint32_t * pos_p)
{
    lv_fs_res_t res = LV_FS_RES_NOT_IMP;

    /*Add your code here*/

    return res;
}

/**
 * Initialize a 'lv_fs_dir_t' variable for directory reading
 * @param drv       pointer to a driver where this function belongs
 * @param path      path to a directory
 * @return          pointer to the directory read descriptor or NULL on error
 */
static void * fs_dir_open(lv_fs_drv_t * drv, const char *path)
{
    void * dir = NULL;
    /*Add your code here*/
    dir = ...           /*Add your code here*/
    return dir;
}

/**
 * Read the next filename form a directory.
 * The name of the directories will begin with '/'
 * @param drv       pointer to a driver where this function belongs
 * @param rddir_p   pointer to an initialized 'lv_fs_dir_t' variable
 * @param fn        pointer to a buffer to store the filename
 * @return          LV_FS_RES_OK: no error or  any error from @lv_fs_res_t enum
 */
static lv_fs_res_t fs_dir_read(lv_fs_drv_t * drv, void * rddir_p, char *fn)
{
    lv_fs_res_t res = LV_FS_RES_NOT_IMP;

    /*Add your code here*/

    return res;
}

/**
 * Close the directory reading
 * @param drv       pointer to a driver where this function belongs
 * @param rddir_p   pointer to an initialized 'lv_fs_dir_t' variable
 * @return          LV_FS_RES_OK: no error or  any error from @lv_fs_res_t enum
 */
static lv_fs_res_t fs_dir_close(lv_fs_drv_t * drv, void * rddir_p)
{
    lv_fs_res_t res = LV_FS_RES_NOT_IMP;

    /*Add your code here*/

    return res;
}

#endif

#else /*Enable this file at the top*/

/*This dummy typedef exists purely to silence -Wpedantic.*/
typedef int keep_pedantic_happy;
#endif
