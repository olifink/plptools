#ifndef _PLP_DIRENT_H_
#define _PLP_DIRENT_H_

#include <string>
#include "psitime.h"
#include "rfsv.h"

/**
 * A class, representing the UIDs of a file on the Psion.
 * Every File on the Psion has a unique UID for determining
 * the application-mapping. This class stores these UIDs.
 * An object of this class is contained in every @ref PlpDirent
 * object.
 *
 * @author Fritz Elfert <felfert@to.com>
 */
class PlpUID
{
	friend inline bool operator<(const PlpUID &u1, const PlpUID &u2);
public:
	/**
	 * Default constructor.
	 */
	PlpUID();

	/**
	 * Constructor.
	 * Create an instance, presetting all thre uid values.
	 */
	PlpUID(const long u1, const long u2, const long u3);

	/**
	 * Retrieve a UID value.
	 *
	 * @param idx The index of the desired UID. Range must be (0..2),
	 *            otherwise an assertion is triggered.
	 */
	long operator[](int idx);

private:
	long uid[3];
};

inline bool operator<(const PlpUID &u1, const PlpUID &u2) {
	return (memcmp(u1.uid, u2.uid, sizeof(u1.uid)) < 0);
}

/**
 * A class, representing a directory entry of the Psion.
 * Objects of this type are used by @ref rfsv::readdir ,
 * @ref rfsv::dir and @ref rfsv::fgeteattr for returning
 * the entries of a directory.
 *
 * @author Fritz Elfert <felfert@to.com>
 */
class PlpDirent {
	friend class rfsv32;
	friend class rfsv16;

public:
	/**
	 * Default constructor
	 */
	PlpDirent() : size(0), attr(0), name(""), time(0L), attrstr("") { };

	/**
	 * A copy constructor.
	 * Mainly used by STL container classes.
	 *
	 * @param d The object to be used as initializer.
	 */
	PlpDirent(const PlpDirent &d);

	/**
	 * Default destructor.
	 */
	~PlpDirent() {};

	/**
	 * Retrieves the file size of a directory entry.
	 *
	 * @returns The file size in bytes.
	 */
	long getSize();

	/**
	 * Retrieves the file attributes of a directory entry.
	 *
	 * @returns The generic attributes ( @ref rfsv:file_attribs ).
	 */
	long getAttr();

	/**
	 * Retrieves the UIDs of a directory entry.
	 * This method returns always 0 with a Series3.
	 *
	 * @param uididx The index of the UID to retrieve (0 .. 2).
	 *
	 * @returns The selected UID or 0 if the index is out of range.
	 */
	long getUID(int uididx);

	/**
	 * Retrieves the @ref PlpUID object of a directory entry.
	 *
	 * @returns The PlpUID object.
	 */
	PlpUID &getUID();

	/**
	 * Retrieve the file name of a directory entry.
	 *
	 * @returns The name of the file.
	 */
	const char *getName();

	/**
	 * Retrieve the modification time of a directory entry.
	 *
	 * @returns A @ref PsiTime object, representing the time.
	 */
	PsiTime getPsiTime();

	/**
	 * Set the file name of a directory entry.
	 * This is currently used in plpbackup only for
	 * changing the name to the full path. It does NOT
	 * change the name of the corresponding file on
	 * the Psion.
	 *
	 * @param str The new name of the file.
	 */
	void setName(const char *str);

	/**
	 * Assignment operator
	 * Mainly used by STL container classes.
	 *
	 * @param e The new value to assign.
	 *
	 * @returns The modified object.
	 */
	PlpDirent &operator=(const PlpDirent &e);

	/**
	 * Prints the object contents.
	 * The output is in human readable similar to the
	 * output of a "ls" command.
	 */
	friend ostream &operator<<(ostream &o, const PlpDirent &e);

private:
	long    size;
	long    attr;
	PlpUID  UID;
	PsiTime time;
	string  attrstr;
	string  name;
};

/**
 * A class representing information about
 * a Disk drive on the psion. An Object of this type
 * is used by @ref rfsv::devinfo for returning the
 * information of the probed drive.
 *
 * @author Fritz Elfert <felfert@to.com>
 */
class PlpDrive {
	friend rfsv32;
	friend rfsv16;

 public:
	/**
	 * Default constructor.
	 */
	PlpDrive();

	/**
	 * Copy constructor
	 */
	PlpDrive(const PlpDrive &other);

	/**
	 * Retrieve the media type of the drive.
	 *
	 * @returns The media type of the probed drive.
	 * <pre>
	 * Media types are encoded by a number
         * in the range 0 .. 8 with the following
	 * meaning:
	 *
	 *   0 = Not present
	 *   1 = Unknown
	 *   2 = Floppy
	 *   3 = Disk
	 *   4 = CD-ROM
	 *   5 = RAM
	 *   6 = Flash Disk
	 *   7 = ROM
	 *   8 = Remote
	 * </pre>
	 */
	u_int32_t getMediaType();

	/**
	 * Retrieve the media type of the drive.
	 * Just like the above function, but returns
	 * the media type as human readable string.
	 *
	 * @param ret The string is returned here.
	 */
	void getMediaType(string &ret);

	/**
	 * Retrieve the attributes of the drive.
	 *
	 * @returns The attributes of the probed drive.
	 * <pre>
	 * Drive attributes are encoded by a number
	 * in the range 0 .. 63. The bits have the
	 * the following meaning:
	 *
	 *   bit 0 = local
	 *   bit 1 = ROM
	 *   bit 2 = redirected
	 *   bit 3 = substituted
	 *   bit 4 = internal
	 *   bit 5 = removable
	 * </pre>
	 */
	u_int32_t getDriveAttribute();

	/**
	 * Retrieve the attributes of the drive.
	 * Just like the above function, but returns
	 * the attributes as human readable string.
	 *
	 * @param ret The string is returned here.
	 */
	void getDriveAttribute(string &ret);

	/**
	 * Retrieve the attributes of the media.
	 *
	 * @returns The attributes of the probed media.
	 * <pre>
	 * Media attributes are encoded by a number
	 * in the range 0 .. 15. The bits have the
	 * following meaning:
	 *
	 *   bit 0 = variable size
	 *   bit 1 = dual density
	 *   bit 2 = formattable
	 *   bit 3 = write protected
	 * </pre>
	 */
	u_int32_t getMediaAttribute();

	/**
	 * Retrieve the attributes of the media.
	 * Just like the above function, but returns
	 * the attributes as human readable string.
	 *
	 * @param ret The string is returned here.
	 */
	void getMediaAttribute(string &ret);

	/**
	 * Retrieve the UID of the drive.
	 * Each drive, except the ROM drive on a Psion has
	 * a unique ID which can be retrieved here.
	 *
	 * @returns The UID of the probed drive.
	 */
	u_int32_t getUID();

	/**
	 * Retrieve the total capacity of the drive.
	 *
	 * @returns The capacity of the probed drive in bytes.
	 */
	u_int64_t getSize();

	/**
	 * Retrieve the free capacity on the drive.
	 *
	 * @returns The free space on the probed drive in bytes.
	 */
	u_int64_t getSpace();

	/**
	 * Retrieve the volume name of the drive.
	 *
	 * returns The volume name of the drive.
	 */
	string getName();

	/**
	 * Retrieve the drive letter of the drive.
	 *
	 * returns The letter of the probed drive.
	 */
	char getDrivechar();

 private:
	void setMediaType(u_int32_t type);
	void setDriveAttribute(u_int32_t attr);
	void setMediaAttribute(u_int32_t attr);
	void setUID(u_int32_t uid);
	void setSize(u_int32_t sizeLo, u_int32_t sizeHi);
	void setSpace(u_int32_t spaceLo, u_int32_t spaceHi);
	void setName(char drive, const char * const volname);

	u_int32_t mediatype;
	u_int32_t driveattr;
	u_int32_t mediaattr;
	u_int32_t uid;
	u_int64_t size;
	u_int64_t space;
	char drivechar;
	string name;
};
#endif