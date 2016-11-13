#include "Recorder.hpp"

#include <gpx/log.hpp>
#include <gpx/phy/RecordableInt.hpp>

#include <fstream>

Recorder::Recorder(std::size_t capacity):
	m_frameCtr(0),
	m_capacity(capacity),
	m_snapshotSize(0),
	m_frames(new char[capacity]),
	m_beginFrame(0),
	m_endFrame(0),
	m_snapFrame(0),
	m_init(false)
{
	GPX_ASSERT(m_capacity > 0, "capacity must be greater than 0 (Recorder(" << m_capacity << ")");
}

Recorder::~Recorder()
{
}

void Recorder::add(gpx::phy::IRecordable * recordable)
{
	m_recordables.push_back(recordable);
	m_snapshotSize += recordable->snapshotSize();
	GPX_DEBUG("recordable added, allocating " << m_capacity * m_snapshotSize << " bytes");
	m_frames.reset(new char[m_capacity * m_snapshotSize]);
}

void Recorder::dump(const char * filename) const
{
	if (!m_init) {
		GPX_WARN("no snapshots to dump");
		return;
	}
	GPX_DEBUG("dumping frames to file " << filename);

	std::size_t snapshotSizeSize_t = gpx::phy::RecordableInt<std::size_t>::SnapshotSize();
	std::unique_ptr<char[]> beginFrameData(new char[snapshotSizeSize_t]);
	std::unique_ptr<char[]> endFrameData(new char[snapshotSizeSize_t]);
	std::unique_ptr<char[]> snapFrameData(new char[snapshotSizeSize_t]);
	std::unique_ptr<char[]> frameCtrData(new char[snapshotSizeSize_t]);
	gpx::phy::RecordableInt<std::size_t>::Store(& beginFrameData[0], m_beginFrame);
	gpx::phy::RecordableInt<std::size_t>::Store(& endFrameData[0], m_endFrame);
	gpx::phy::RecordableInt<std::size_t>::Store(& snapFrameData[0], m_snapFrame);
	gpx::phy::RecordableInt<std::size_t>::Store(& frameCtrData[0], m_frameCtr);

	std::fstream fs;
	fs.open(filename, std::ios_base::out | std::ios_base::binary);
	fs.write(& beginFrameData[0], snapshotSizeSize_t);
	fs.write(& endFrameData[0], snapshotSizeSize_t);
	fs.write(& snapFrameData[0], snapshotSizeSize_t);
	fs.write(& frameCtrData[0], snapshotSizeSize_t);
	fs.write(& m_frames[0], m_snapshotSize * m_capacity);
	fs.close();
}

void Recorder::load(const char * filename)
{
	GPX_DEBUG("loading file " << filename);

	std::size_t snapshotSizeSize_t = gpx::phy::RecordableInt<std::size_t>::SnapshotSize();
	std::unique_ptr<char[]> beginFrameData(new char[snapshotSizeSize_t]);
	std::unique_ptr<char[]> endFrameData(new char[snapshotSizeSize_t]);
	std::unique_ptr<char[]> snapFrameData(new char[snapshotSizeSize_t]);
	std::unique_ptr<char[]> frameCtrData(new char[snapshotSizeSize_t]);

	std::fstream fs;
	fs.open(filename, std::ios_base::in | std::ios_base::binary);
	fs.read(& beginFrameData[0], snapshotSizeSize_t);
	fs.read(& endFrameData[0], snapshotSizeSize_t);
	fs.read(& snapFrameData[0], snapshotSizeSize_t);
	fs.read(& frameCtrData[0], snapshotSizeSize_t);
	fs.read(& m_frames[0], m_snapshotSize * m_capacity);
	fs.close();

	gpx::phy::RecordableInt<std::size_t>::Restore(& beginFrameData[0], m_beginFrame);
	gpx::phy::RecordableInt<std::size_t>::Restore(& endFrameData[0], m_endFrame);
	gpx::phy::RecordableInt<std::size_t>::Restore(& snapFrameData[0], m_snapFrame);
	gpx::phy::RecordableInt<std::size_t>::Restore(& frameCtrData[0], m_frameCtr);
	m_init = true;
	restoreSnap();
}

void Recorder::rewind()
{
	if (m_snapFrame == m_beginFrame)
		return;
	if (m_snapFrame == 0)
		m_snapFrame = m_capacity;
	m_snapFrame--;
	m_frameCtr--;
	GPX_DEBUG("################# rewind to frame " << m_frameCtr << " #################");
	restoreSnap();
}

void Recorder::forward()
{
	if (m_snapFrame == m_endFrame)
		return;
	m_snapFrame++;
	m_snapFrame %= m_capacity;
	m_frameCtr++;
	GPX_DEBUG("################# forward to frame " << m_frameCtr << " #################");
	restoreSnap();
}

void Recorder::restoreSnap()
{
	char * framePtr = & m_frames[m_snapFrame * m_snapshotSize];
	for (auto r = m_recordables.begin(); r != m_recordables.end(); ++r) {
		(*r)->restore(framePtr);
		framePtr += (*r)->snapshotSize();
	}
}

void Recorder::snapshot()
{
	if (m_init) {
		m_snapFrame++;
		m_snapFrame %= m_capacity;
		m_endFrame = m_snapFrame;
		if (m_endFrame == m_beginFrame) {
			m_beginFrame++;
			m_beginFrame %= m_capacity;
		}
		m_frameCtr++;
	} else
		m_init = true;
	GPX_DEBUG("################# frame " << m_frameCtr << " #################");

	char * framePtr = & m_frames[m_snapFrame * m_snapshotSize];
	for (auto r = m_recordables.begin(); r != m_recordables.end(); ++r) {
//		GPX_DEBUG("storing object and advancing pointer by " << (*r)->snapshotSize() << " bytes");
		(*r)->store(framePtr);
		framePtr += (*r)->snapshotSize();
	}
}

