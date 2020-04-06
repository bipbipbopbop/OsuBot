#ifndef OSUKEY_HPP
# define OSUKEY_HPP

# include <cstddef>
# include <string>

/*
 * Values may or may not be represented by a Key.
 * A Key may or may not be associated with a value. A Key is represented by
 * a OsuKey class, wich hold either a size_t (used as an index for unnamed values)
 * or a std::string.
 */
class OsuKey
{
public:
	// The Tag enum define what is stored in the OsuKey.
	enum class Tag { Index, String, Empty };

	OsuKey();
	OsuKey(size_t val);
	OsuKey(std::string val);
	~OsuKey();

	OsuKey(const OsuKey &other);
	OsuKey(OsuKey &&other);
	OsuKey		&operator=(OsuKey other);

	bool		operator==(const OsuKey &other) const;
	bool		operator!=(const OsuKey &other) const;
	bool		operator<(const OsuKey &other) const;
	bool		operator<=(const OsuKey &other) const;
	bool		operator>(const OsuKey &other) const;
	bool		operator>=(const OsuKey &other) const;

	friend void	swap(OsuKey &lhs, OsuKey &rhs) noexcept;

	Tag					getType() const;
	size_t				&getIndex();
	size_t				getIndex() const;
	std::string			&getStr();
	const std::string	&getStr() const;

private:
	Tag			_type;
	void		*_val;
};

std::ostream	&operator<<(std::ostream &os, const OsuKey &rhs);


#endif // OSUKEY_HPP
