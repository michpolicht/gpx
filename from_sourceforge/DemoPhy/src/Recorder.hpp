#ifndef RECORDER_HPP
#define RECORDER_HPP

#include <gpx/phy/IRecordable.hpp>
#include <vector>
#include <memory>

class Recorder
{
	public:
		Recorder(std::size_t capacity = 100);

		virtual ~Recorder();

		void add(gpx::phy::IRecordable * recordable);

		void dump(const char * filename) const;

		void load(const char * filename);

		void rewind();

		void forward();

		void snapshot();

	private:
		typedef std::vector<gpx::phy::IRecordable *> RecordablesContainer;

		void restoreSnap();

		std::size_t m_frameCtr;
		std::size_t m_capacity;
		std::size_t m_snapshotSize;
		std::unique_ptr<char[]> m_frames;
		std::size_t m_beginFrame;
		std::size_t m_endFrame;
		std::size_t m_snapFrame;
		bool m_init;
		RecordablesContainer m_recordables;
};

#endif // RECORDER_HPP
