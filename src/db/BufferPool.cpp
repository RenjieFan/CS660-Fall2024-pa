#include <db/BufferPool.hpp>
#include <db/Database.hpp>
#include <numeric>

using namespace db;

BufferPool::BufferPool()
// TODO pa1: add initializations if needed
{
  // TODO pa1: additional initialization if needed
}

BufferPool::~BufferPool() {
  // TODO pa1: flush any remaining dirty pages
}

Page &BufferPool::getPage(const PageId &pid) {
  // TODO pa1: If already in buffer pool, make it the most recent page and return it

  // TODO pa1: If there are no available pages, evict the least recently used page. If it is dirty, flush it to disk

  // TODO pa1: Read the page from disk to one of the available slots, make it the most recent page
}

void BufferPool::markDirty(const PageId &pid) {
   if (!contains(pid)) {
            throw std::runtime_error("Page not in buffer pool");
   }
        page_map[pid]->is_dirty = true;
  // TODO pa1: Mark the page as dirty. Note that the page must already be in the buffer pool
}

bool BufferPool::isDirty(const PageId &pid) const {
   if (!contains(pid)) {
            throw std::runtime_error("Page not in buffer pool");
        }
        return page_map.at(pid)->is_dirty;
  // TODO pa1: Return whether the page is dirty. Note that the page must already be in the buffer pool
}

bool BufferPool::contains(const PageId &pid) const {
   return page_map.find(pid) != page_map.end();
  // TODO pa1: Return whether the page is in the buffer pool
}

void BufferPool::discardPage(const PageId &pid) {
  if (!contains(pid)) {
            return;
        }
        auto it = page_map[pid];
        lru_list.erase(it);
        page_map.erase(pid);
  // TODO pa1: Discard the page from the buffer pool. Note that the page must already be in the buffer pool
}

void BufferPool::flushPage(const PageId &pid) {
  if (!contains(pid)) {
            throw std::runtime_error("Page not in buffer pool");
        }
        auto it = page_map[pid];
        if (it->is_dirty) {
            Database::getFileManager().writePage(it->page);
            it->is_dirty = false;
        }
  // TODO pa1: Flush the page to disk. Note that the page must already be in the buffer pool
}

void BufferPool::flushFile(const std::string &file) {
  // TODO pa1: Flush all pages of the file to disk
}
