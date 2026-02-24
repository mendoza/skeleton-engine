#pragma once
#include <functional>
#include <memory>
#include <skeleton/math/types.hpp>
#include <vector>

namespace skeleton::core {

// ─── helpers ────────────────────────────────────────────────────────────────

inline bool qt_contains(const skeleton::Rect &r, skeleton::Vec2 p) {
  return p.x >= r.x && p.x < r.x + r.w && p.y >= r.y && p.y < r.y + r.h;
}

inline bool qt_overlaps(const skeleton::Rect &a, const skeleton::Rect &b) {
  return a.x < b.x + b.w && a.x + a.w > b.x && a.y < b.y + b.h &&
         a.y + a.h > b.y;
}

// ─── Quadtree ───────────────────────────────────────────────────────────────

// Spatial index that partitions 2D space recursively into four quadrants.
//
// Usage:
//   Quadtree<entt::entity> qt({0, 0, 1920, 1080});
//   qt.insert({px, py}, entity);
//   std::vector<entt::entity> near;
//   qt.query({mx - 64, my - 64, 128, 128}, near);
//
// Call clear() + re-insert every frame for dynamic objects.
//
template <typename T> class Quadtree {
public:
  struct Item {
    skeleton::Vec2 pos;
    T value;
  };

  // bounds    — world-space AABB this node covers (x, y, w, h)
  // capacity  — max items per node before splitting
  // max_depth — hard limit on recursion depth (prevents infinite splits on
  //             coincident points)
  explicit Quadtree(skeleton::Rect bounds, int capacity = 8, int max_depth = 8)
      : bounds_(bounds), capacity_(capacity), max_depth_(max_depth) {}

  // Insert value at world position pos.
  // Silently ignores points outside the root bounds.
  void insert(skeleton::Vec2 pos, T value) { insert_item({pos, value}, 0); }

  // Append to `out` all values whose positions fall inside `range`.
  void query(skeleton::Rect range, std::vector<T> &out) const {
    if (!qt_overlaps(bounds_, range))
      return;
    for (const auto &item : items_)
      if (qt_contains(range, item.pos))
        out.push_back(item.value);
    if (divided_)
      for (const auto &child : children_)
        child->query(range, out);
  }

  // Convenience overload — returns a new vector.
  std::vector<T> query(skeleton::Rect range) const {
    std::vector<T> out;
    query(range, out);
    return out;
  }

  // Remove all items and collapse children. O(n nodes).
  void clear() {
    items_.clear();
    divided_ = false;
    for (auto &c : children_)
      c.reset();
  }

  skeleton::Rect bounds() const { return bounds_; }
  bool divided() const { return divided_; }

  // Walk every node's bounding rect — use for debug visualization.
  // Example:
  //   qt.visit_bounds([&](const Rect &r) {
  //     renderer.draw_rect(r, {0, 255, 0, 80});
  //   });
  void
  visit_bounds(const std::function<void(const skeleton::Rect &)> &fn) const {
    fn(bounds_);
    if (divided_)
      for (const auto &child : children_)
        child->visit_bounds(fn);
  }

private:
  void insert_item(Item item, int depth) {
    if (!qt_contains(bounds_, item.pos))
      return;

    if (divided_) {
      // Push into the child that owns this point.
      for (auto &child : children_) {
        if (qt_contains(child->bounds_, item.pos)) {
          child->insert_item(item, depth + 1);
          return;
        }
      }
      // Boundary edge: no child claims it — keep in parent.
      items_.push_back(item);
      return;
    }

    items_.push_back(item);

    if ((int)items_.size() > capacity_ && depth < max_depth_)
      subdivide(depth);
  }

  void subdivide(int depth) {
    float hx = bounds_.w / 2.0f;
    float hy = bounds_.h / 2.0f;
    float cx = bounds_.x + hx;
    float cy = bounds_.y + hy;

    //  NW            NE
    //  [0] bounds_.x [1] cx
    //  SW            SE
    //  [2] bounds_.x [3] cx
    children_[0] = std::make_unique<Quadtree>(
        skeleton::Rect{bounds_.x, bounds_.y, hx, hy}, capacity_, max_depth_);
    children_[1] = std::make_unique<Quadtree>(
        skeleton::Rect{cx, bounds_.y, hx, hy}, capacity_, max_depth_);
    children_[2] = std::make_unique<Quadtree>(
        skeleton::Rect{bounds_.x, cy, hx, hy}, capacity_, max_depth_);
    children_[3] = std::make_unique<Quadtree>(skeleton::Rect{cx, cy, hx, hy},
                                              capacity_, max_depth_);
    divided_ = true;

    // Redistribute existing items into children; un-claimable items stay here.
    std::vector<Item> orphans;
    for (auto &item : items_) {
      bool placed = false;
      for (auto &child : children_) {
        if (qt_contains(child->bounds_, item.pos)) {
          child->insert_item(item, depth + 1);
          placed = true;
          break;
        }
      }
      if (!placed)
        orphans.push_back(item);
    }
    items_ = std::move(orphans);
  }

  skeleton::Rect bounds_;
  int capacity_;
  int max_depth_;

  std::vector<Item> items_;
  bool divided_ = false;
  std::unique_ptr<Quadtree> children_[4]; // NW, NE, SW, SE
};

} // namespace skeleton::core
