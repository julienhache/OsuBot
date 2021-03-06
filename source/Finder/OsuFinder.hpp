#ifndef OSUFINDER_HPP
# define OSUFINDER_HPP

# include <string>

typedef void	*HANDLE;

/*
 * Finder:
 * This class will store a valid process handle (with no ownership), and automatically
 * found where the corresponding executable is stored.
 * This do not work with the special handle value returned by GetCurrentProcess().
 */
class Finder
{
public:
	Finder();
	Finder(HANDLE processHandle);
	Finder(const Finder &other) = default;
	Finder(Finder &&other) = default;
	~Finder() = default;

	Finder	&operator=(const Finder &rhs) = default;
	Finder	&operator=(Finder &&rhs) = default;

	bool		isHandleValid() const;
	/*
	 * setProcessHandle(HANDLE):
	 * when setting a new process handle, the Finder instance will look for
	 * the directory containing the process, and set this value in _processDirectory.
	 */
	void		setProcessHandle(HANDLE processHandle);
	HANDLE		getProcessHandle() const;
	std::string	getProcessDir() const;

protected:
	HANDLE		_processHandle;
	std::string	_processDirectory;
};

/*
 * OsuFinder:
 * This class will look for a running Osu! process, and retrieve the directory of the executable.
 * From this, we can easily look for a map, using the findMap() method.
 */
class OsuFinder: public Finder
{
public:
	OsuFinder();
	OsuFinder(HANDLE OsuProcesshandle);

	/*
	 * findMap(std::string):
	 * Search for, in the {OsuDirectory}/Songs directory, a folder
	 * wich name contains the hint given by the 'mapName' parameter,
	 * and return the first corresponding directory.
	 * You can give the name or the songID of the map as parameter.
	 *
	 * If no corresponding folder is found, an empty string is returned.
	 */
	std::string	findMap(std::string mapName) const;
};


#endif // OSUFINDER_HPP