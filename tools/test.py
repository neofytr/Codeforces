import tkinter as tk
from tkinter import ttk, messagebox, filedialog
import random
from collections import deque
import json


class Room:
    def __init__(self, name, w, h):
        self.name = name
        self.w, self.h = w, h
        self.x = self.y = 0
        self.rotated = False

    def rotate(self):
        self.w, self.h = self.h, self.w
        self.rotated = not self.rotated

    def area(self):
        return self.w * self.h

    def bounds(self):
        return (self.x, self.y, self.x + self.w, self.y + self.h)

    def center(self):
        return (self.x + self.w / 2, self.y + self.h / 2)


class Corridor:
    def __init__(self, x, y, w, h):
        self.x, self.y, self.w, self.h = x, y, w, h

    def bounds(self):
        return (self.x, self.y, self.x + self.w, self.y + self.h)


class FloorPlanner:
    def __init__(self, plot_w, plot_h, rooms, corridor_width=3):
        self.pw, self.ph = plot_w, plot_h
        self.original_rooms = rooms
        self.rooms = []
        self.cw = corridor_width
        self.solutions = []

    def is_valid(self):
        total_room_area = sum(r[1] * r[2] for r in self.original_rooms)
        plot_area = self.pw * self.ph
        return total_room_area <= 0.7 * plot_area

    def create_rooms(self):
        return [Room(r[0], r[1], r[2]) for r in self.original_rooms]

    def rectangles_overlap(self, b1, b2, margin=0):
        x1, y1, x2, y2 = b1
        x3, y3, x4, y4 = b2
        return not (x2 + margin <= x3 or x4 + margin <= x1 or
                    y2 + margin <= y3 or y4 + margin <= y1)

    def generate_corridor_network(self, placed_rooms):
        corridors = []
        n = len(placed_rooms)

        for i in range(n):
            for j in range(i + 1, n):
                r1, r2 = placed_rooms[i], placed_rooms[j]
                x1, y1, x2, y2 = r1.bounds()
                x3, y3, x4, y4 = r2.bounds()

                h_overlap = not (y2 <= y3 or y4 <= y1)
                v_overlap = not (x2 <= x3 or x4 <= x1)

                if h_overlap:
                    if x2 < x3 and x3 - x2 <= 2 * self.cw:
                        cy1 = max(y1, y3)
                        cy2 = min(y2, y4)
                        if cy2 - cy1 >= self.cw:
                            corridors.append(Corridor(x2, cy1, x3 - x2, self.cw))

                    elif x4 < x1 and x1 - x4 <= 2 * self.cw:
                        cy1 = max(y1, y3)
                        cy2 = min(y2, y4)
                        if cy2 - cy1 >= self.cw:
                            corridors.append(Corridor(x4, cy1, x1 - x4, self.cw))

                if v_overlap:
                    if y2 < y3 and y3 - y2 <= 2 * self.cw:
                        cx1 = max(x1, x3)
                        cx2 = min(x2, x4)
                        if cx2 - cx1 >= self.cw:
                            corridors.append(Corridor(cx1, y2, self.cw, y3 - y2))

                    elif y4 < y1 and y1 - y4 <= 2 * self.cw:
                        cx1 = max(x1, x3)
                        cx2 = min(x2, x4)
                        if cx2 - cx1 >= self.cw:
                            corridors.append(Corridor(cx1, y4, self.cw, y1 - y4))

        main_corridor_h = Corridor(self.cw, self.ph // 2 - self.cw // 2,
                                   self.pw - 2 * self.cw, self.cw)
        main_corridor_v = Corridor(self.pw // 2 - self.cw // 2, self.cw,
                                   self.cw, self.ph - 2 * self.cw)

        room_overlap_h = any(self.rectangles_overlap(main_corridor_h.bounds(), r.bounds())
                             for r in placed_rooms)
        room_overlap_v = any(self.rectangles_overlap(main_corridor_v.bounds(), r.bounds())
                             for r in placed_rooms)

        if not room_overlap_h:
            corridors.append(main_corridor_h)
        if not room_overlap_v:
            corridors.append(main_corridor_v)

        return corridors

    def verify_connectivity(self, placed_rooms, corridors):
        if len(placed_rooms) <= 1:
            return True

        adjacency = {i: set() for i in range(len(placed_rooms))}

        for c in corridors:
            cx1, cy1, cx2, cy2 = c.bounds()
            adjacent_rooms = []

            for i, r in enumerate(placed_rooms):
                rx1, ry1, rx2, ry2 = r.bounds()

                if (abs(rx2 - cx1) <= 1 or abs(cx2 - rx1) <= 1 or
                        abs(ry2 - cy1) <= 1 or abs(cy2 - ry1) <= 1):
                    if self.rectangles_overlap((cx1, cy1, cx2, cy2),
                                               (rx1 - 1, ry1 - 1, rx2 + 1, ry2 + 1)):
                        adjacent_rooms.append(i)

            for i in adjacent_rooms:
                for j in adjacent_rooms:
                    if i != j:
                        adjacency[i].add(j)
                        adjacency[j].add(i)

        visited = set([0])
        queue = deque([0])

        while queue:
            current = queue.popleft()
            for neighbor in adjacency[current]:
                if neighbor not in visited:
                    visited.add(neighbor)
                    queue.append(neighbor)

        return len(visited) == len(placed_rooms)

    def place_rooms_strategy(self, rooms, strategy):
        placed = []

        if strategy == 'linear':
            x_pos = self.cw
            for r in sorted(rooms, key=lambda x: -x.w):
                r.x, r.y = x_pos, self.cw
                if r.x + r.w + self.cw <= self.pw and r.y + r.h + self.cw <= self.ph:
                    placed.append(r)
                    x_pos += r.w + self.cw
                else:
                    return None

        elif strategy == 'grid':
            grid = sorted(rooms, key=lambda x: -x.area())
            positions = []

            for x in range(self.cw, self.pw, self.cw):
                for y in range(self.cw, self.ph, self.cw):
                    positions.append((x, y))

            random.shuffle(positions)

            for r in grid:
                placed_room = False
                for x, y in positions:
                    r.x, r.y = x, y

                    if r.x + r.w + self.cw > self.pw or r.y + r.h + self.cw > self.ph:
                        continue

                    overlap = False
                    for pr in placed:
                        if self.rectangles_overlap(r.bounds(), pr.bounds(), self.cw):
                            overlap = True
                            break

                    if not overlap:
                        placed.append(r)
                        placed_room = True
                        break

                if not placed_room:
                    return None

        elif strategy == 'clustered':
            if not rooms:
                return None

            large_rooms = sorted([r for r in rooms if r.area() >= 60], key=lambda x: -x.area())
            small_rooms = sorted([r for r in rooms if r.area() < 60], key=lambda x: -x.area())

            if large_rooms:
                r = large_rooms[0]
                r.x = self.pw // 2 - r.w // 2
                r.y = self.ph // 2 - r.h // 2
                placed.append(r)
                remaining = large_rooms[1:] + small_rooms
            else:
                remaining = small_rooms

            for r in remaining:
                best_pos = None
                min_distance = float('inf')

                candidates = []
                for pr in placed:
                    candidates.extend([
                        (pr.x + pr.w + self.cw, pr.y),
                        (pr.x, pr.y + pr.h + self.cw),
                        (max(self.cw, pr.x - r.w - self.cw), pr.y),
                        (pr.x, max(self.cw, pr.y - r.h - self.cw))
                    ])

                for x, y in candidates:
                    r.x, r.y = x, y

                    if r.x + r.w + self.cw > self.pw or r.y + r.h + self.cw > self.ph:
                        continue

                    valid = True
                    for pr in placed:
                        if self.rectangles_overlap(r.bounds(), pr.bounds(), self.cw):
                            valid = False
                            break

                    if valid:
                        cx, cy = r.center()
                        dist = min((cx - pr.center()[0]) ** 2 + (cy - pr.center()[1]) ** 2
                                   for pr in placed)
                        if dist < min_distance:
                            min_distance = dist
                            best_pos = (x, y)

                if best_pos:
                    r.x, r.y = best_pos
                    placed.append(r)
                else:
                    return None

        elif strategy == 'corners':
            corners = [
                (self.cw, self.cw),
                (self.pw - self.cw, self.cw),
                (self.cw, self.ph - self.cw),
                (self.pw - self.cw, self.ph - self.cw)
            ]

            sorted_rooms = sorted(rooms, key=lambda x: -x.area())

            for i, r in enumerate(sorted_rooms[:4]):
                cx, cy = corners[i]
                r.x = cx if cx == self.cw else cx - r.w - self.cw
                r.y = cy if cy == self.cw else cy - r.h - self.cw

                if r.x < self.cw or r.y < self.cw:
                    continue
                if r.x + r.w + self.cw > self.pw or r.y + r.h + self.cw > self.ph:
                    continue

                placed.append(r)

            for r in sorted_rooms[4:]:
                best_pos = None
                min_metric = float('inf')

                for x in range(self.cw, self.pw - r.w - self.cw, self.cw):
                    for y in range(self.cw, self.ph - r.h - self.cw, self.cw):
                        r.x, r.y = x, y

                        valid = True
                        for pr in placed:
                            if self.rectangles_overlap(r.bounds(), pr.bounds(), self.cw):
                                valid = False
                                break

                        if valid:
                            metric = sum(abs(x - pr.x) + abs(y - pr.y) for pr in placed)
                            if metric < min_metric:
                                min_metric = metric
                                best_pos = (x, y)

                if best_pos:
                    r.x, r.y = best_pos
                    placed.append(r)
                else:
                    return None

        return placed if len(placed) == len(rooms) else None

    def generate_solutions(self, max_solutions=10, max_attempts=1000):
        if not self.is_valid():
            return []

        n = len(self.original_rooms)
        strategies = ['grid', 'clustered', 'corners', 'linear']
        checked = set()
        attempts = 0

        while len(self.solutions) < max_solutions and attempts < max_attempts:
            rotation_mask = random.randint(0, (1 << n) - 1)
            strategy = strategies[attempts % len(strategies)]

            key = (rotation_mask, strategy)
            if key in checked:
                attempts += 1
                continue

            checked.add(key)

            rooms = self.create_rooms()
            for i, r in enumerate(rooms):
                if rotation_mask & (1 << i):
                    r.rotate()

            placed = self.place_rooms_strategy(rooms, strategy)

            if placed:
                corridors = self.generate_corridor_network(placed)

                if self.verify_connectivity(placed, corridors):
                    layout = (
                        [(r.name, r.x, r.y, r.w, r.h, r.rotated) for r in placed],
                        [(c.x, c.y, c.w, c.h) for c in corridors]
                    )

                    room_data = tuple(sorted([(r[0], r[1], r[2], r[3], r[4]) for r in layout[0]]))
                    if room_data not in [tuple(sorted([(r[0], r[1], r[2], r[3], r[4])
                                                       for r in sol[0]])) for sol in self.solutions]:
                        self.solutions.append(layout)

            attempts += 1

        return self.solutions


class FloorPlannerGUI:
    def __init__(self, root):
        self.root = root
        self.root.title("Floor Plan Generator")
        self.root.geometry("1400x900")
        self.root.configure(bg='#f0f0f0')

        style = ttk.Style()
        style.theme_use('clam')
        style.configure('Title.TLabel', font=('Segoe UI', 14, 'bold'), background='#f0f0f0')
        style.configure('Subtitle.TLabel', font=('Segoe UI', 10), background='#f0f0f0')
        style.configure('TButton', font=('Segoe UI', 10), padding=6)
        style.configure('Action.TButton', font=('Segoe UI', 11, 'bold'))

        self.setup_ui()
        self.current_solution = 0
        self.planner = None
        self.view_mode = '2d'
        self.root.after(100, self.draw_welcome_screen)

    def setup_ui(self):
        main_container = ttk.Frame(self.root)
        main_container.pack(fill='both', expand=True, padx=10, pady=10)

        left_panel = ttk.Frame(main_container)
        left_panel.pack(side='left', fill='y', padx=(0, 10))

        header = ttk.Label(left_panel, text="Floor Plan Generator", style='Title.TLabel')
        header.pack(pady=(0, 20))

        plot_frame = ttk.LabelFrame(left_panel, text="Plot Configuration", padding=15)
        plot_frame.pack(fill='x', pady=(0, 15))

        ttk.Label(plot_frame, text="Width (units):").grid(row=0, column=0, sticky='w', pady=5)
        self.plot_w = ttk.Entry(plot_frame, width=12)
        self.plot_w.insert(0, "45")
        self.plot_w.grid(row=0, column=1, pady=5, padx=(10, 0))

        ttk.Label(plot_frame, text="Height (units):").grid(row=1, column=0, sticky='w', pady=5)
        self.plot_h = ttk.Entry(plot_frame, width=12)
        self.plot_h.insert(0, "35")
        self.plot_h.grid(row=1, column=1, pady=5, padx=(10, 0))

        ttk.Label(plot_frame, text="Corridor Width:").grid(row=2, column=0, sticky='w', pady=5)
        self.corridor_w = ttk.Entry(plot_frame, width=12)
        self.corridor_w.insert(0, "3")
        self.corridor_w.grid(row=2, column=1, pady=5, padx=(10, 0))

        rooms_frame = ttk.LabelFrame(left_panel, text="Room Specifications", padding=15)
        rooms_frame.pack(fill='both', expand=True, pady=(0, 15))

        ttk.Label(rooms_frame, text="Format: Name,Width,Height",
                  style='Subtitle.TLabel').pack(anchor='w', pady=(0, 5))

        scroll = ttk.Scrollbar(rooms_frame)
        scroll.pack(side='right', fill='y')

        self.room_text = tk.Text(rooms_frame, width=32, height=18,
                                 font=('Consolas', 10), yscrollcommand=scroll.set)
        self.room_text.insert("1.0", "Living Room,14,12\nMaster Bedroom,12,11\nBedroom 2,10,10\n"
                                     "Kitchen,10,8\nDining,9,8\nBathroom 1,6,5\nBathroom 2,5,5")
        self.room_text.pack(fill='both', expand=True)
        scroll.config(command=self.room_text.yview)

        button_frame = ttk.Frame(rooms_frame)
        button_frame.pack(fill='x', pady=(10, 0))

        ttk.Button(button_frame, text="Load", command=self.load_config,
                   width=10).pack(side='left', padx=(0, 5))
        ttk.Button(button_frame, text="Save", command=self.save_config,
                   width=10).pack(side='left')

        generate_btn = ttk.Button(left_panel, text="Generate Floor Plans",
                                  command=self.generate, style='Action.TButton')
        generate_btn.pack(fill='x', pady=(0, 15))

        nav_frame = ttk.LabelFrame(left_panel, text="Navigation", padding=10)
        nav_frame.pack(fill='x', pady=(0, 15))

        btn_frame = ttk.Frame(nav_frame)
        btn_frame.pack(fill='x', pady=(0, 10))

        ttk.Button(btn_frame, text="◀ Previous", command=self.prev_solution,
                   width=12).pack(side='left', padx=(0, 5))
        ttk.Button(btn_frame, text="Next ▶", command=self.next_solution,
                   width=12).pack(side='right')

        self.solution_label = ttk.Label(nav_frame, text="No solutions generated",
                                        font=('Segoe UI', 10, 'bold'))
        self.solution_label.pack()

        stats_frame = ttk.LabelFrame(left_panel, text="Statistics", padding=15)
        stats_frame.pack(fill='x')

        self.stats_text = tk.Text(stats_frame, width=32, height=8,
                                  font=('Consolas', 9), state='disabled',
                                  relief='flat', background='#f9f9f9')
        self.stats_text.pack(fill='x')

        right_panel = ttk.Frame(main_container)
        right_panel.pack(side='right', fill='both', expand=True)

        canvas_header = ttk.Frame(right_panel)
        canvas_header.pack(fill='x', pady=(0, 10))

        ttk.Label(canvas_header, text="Floor Plan View",
                  style='Title.TLabel').pack(side='left')

        view_frame = ttk.Frame(canvas_header)
        view_frame.pack(side='right')

        self.view_2d = ttk.Radiobutton(view_frame, text="2D View", value='2d',
                                       command=self.change_view)
        self.view_2d.pack(side='left', padx=5)
        self.view_2d.invoke()

        self.view_3d = ttk.Radiobutton(view_frame, text="3D View", value='3d',
                                       command=self.change_view)
        self.view_3d.pack(side='left', padx=5)

        canvas_frame = ttk.Frame(right_panel, relief='solid', borderwidth=1)
        canvas_frame.pack(fill='both', expand=True)

        self.canvas = tk.Canvas(canvas_frame, bg='white', highlightthickness=0)
        self.canvas.pack(fill='both', expand=True, padx=2, pady=2)

        self.draw_welcome_screen()

    def draw_welcome_screen(self):
        self.canvas.delete("all")
        w = self.canvas.winfo_width()
        h = self.canvas.winfo_height()



        if w < 100:
            w = 900
            h = 700

        self.canvas.create_text(w / 2, h / 2 - 30,
                        text="Floor Plan Generator",
                        font=('Segoe UI', 24, 'bold'),
                        fill='#333')
        self.canvas.create_text(w / 2, h / 2 + 10,
                        text="Configure your plot and rooms, then click Generate",
                        font=('Segoe UI', 12),
                        fill='#666')
        self.canvas.create_text(w / 2, h / 2 + 40,
                        text="The system will create multiple valid layouts with corridors",
                        font=('Segoe UI', 11),
                        fill='#999')

    def change_view(self):
        self.view_mode = '2d' if self.view_2d.instate(['selected']) else '3d'
        if self.planner and self.planner.solutions:
            self.draw_solution()

    def parse_rooms(self):
        rooms = []
        for line in self.room_text.get("1.0", "end").strip().split("\n"):
            line = line.strip()
            if not line or line.startswith('#'):
                continue
            parts = [p.strip() for p in line.split(",")]
            if len(parts) >= 3:
                try:
                    rooms.append((parts[0], int(parts[1]), int(parts[2])))
                except ValueError:
                    continue
        return rooms

    def generate(self):
        try:
            pw = int(self.plot_w.get())
            ph = int(self.plot_h.get())
            cw = int(self.corridor_w.get())
            rooms = self.parse_rooms()

            if not rooms:
                messagebox.showerror("Error", "Please add at least one room")
                return

            if pw < 10 or ph < 10:
                messagebox.showerror("Error", "Plot dimensions must be at least 10 units")
                return

            if cw < 2 or cw > 5:
                messagebox.showerror("Error", "Corridor width must be between 2 and 5 units")
                return

            self.planner = FloorPlanner(pw, ph, rooms, cw)

            if not self.planner.is_valid():
                total_area = sum(r[1] * r[2] for r in rooms)
                plot_area = pw * ph
                messagebox.showerror("Error",
                                     f"Rooms occupy {total_area} units ({100 * total_area / plot_area:.1f}%)\n"
                                     f"Maximum allowed: {int(0.7 * plot_area)} units (70%)\n\n"
                                     f"Please reduce room sizes or increase plot area")
                return

            self.solution_label.config(text="Generating layouts...")
            self.root.update()

            solutions = self.planner.generate_solutions(10, 1500)

            if not solutions:
                messagebox.showwarning("No Solutions",
                                       "Could not find valid layouts.\n\n"
                                       "Suggestions:\n"
                                       "• Increase plot dimensions\n"
                                       "• Reduce room sizes\n"
                                       "• Reduce corridor width\n"
                                       "• Use fewer rooms")
                self.solution_label.config(text="No solutions found")
                return

            self.current_solution = 0
            self.draw_solution()
            messagebox.showinfo("Success",
                                f"Generated {len(solutions)} unique floor plan layouts!\n\n"
                                f"Use the navigation buttons to explore different arrangements.")

        except ValueError as e:
            messagebox.showerror("Invalid Input",
                                 f"Please check your input values:\n{str(e)}")

    def prev_solution(self):
        if self.planner and self.planner.solutions:
            self.current_solution = (self.current_solution - 1) % len(self.planner.solutions)
            self.draw_solution()

    def next_solution(self):
        if self.planner and self.planner.solutions:
            self.current_solution = (self.current_solution + 1) % len(self.planner.solutions)
            self.draw_solution()

    def draw_solution(self):
        if not self.planner or not self.planner.solutions:
            return

        if self.view_mode == '2d':
            self.draw_2d()
        else:
            self.draw_3d()

        self.update_statistics()

    def draw_2d(self):
        self.canvas.delete("all")

        rooms_layout, corridors_layout = self.planner.solutions[self.current_solution]

        w = self.canvas.winfo_width()
        h = self.canvas.winfo_height()
        margin = 50

        scale = min((w - 2 * margin) / self.planner.pw,
                    (h - 2 * margin) / self.planner.ph)

        offset_x = margin + (w - 2 * margin - self.planner.pw * scale) / 2
        offset_y = margin + (h - 2 * margin - self.planner.ph * scale) / 2

        self.canvas.create_rectangle(
            offset_x - 5, offset_y - 5,
            offset_x + self.planner.pw * scale + 5,
            offset_y + self.planner.ph * scale + 5,
            fill='#e8e8e8', outline='#999', width=3
        )

        self.canvas.create_text(offset_x + self.planner.pw * scale / 2,
                                offset_y - 25,
                                text=f"Plot Boundary: {self.planner.pw} × {self.planner.ph} units",
                                font=('Segoe UI', 11, 'bold'), fill='#333')

        for cx, cy, cw, ch in corridors_layout:
            x1 = offset_x + cx * scale
            y1 = offset_y + cy * scale
            x2 = x1 + cw * scale
            y2 = y1 + ch * scale

            self.canvas.create_rectangle(x1, y1, x2, y2,
                                         fill='#d4d4d4', outline='#aaa', width=1,
                                         stipple='gray50')

        colors = ['#FF6B6B', '#4ECDC4', '#95E1D3', '#F38181', '#AA96DA',
                  '#FCBAD3', '#FFFFD2', '#A8D8EA', '#FFCBC1', '#C7CEEA']

        for i, (name, x, y, w, h, rotated) in enumerate(rooms_layout):
            x1 = offset_x + x * scale
            y1 = offset_y + y * scale
            x2 = x1 + w * scale
            y2 = y1 + h * scale

            color = colors[i % len(colors)]

            self.canvas.create_rectangle(x1, y1, x2, y2,
                                         fill=color, outline='#333', width=2)

            cx = (x1 + x2) / 2
            cy = (y1 + y2) / 2

            self.canvas.create_text(cx, cy - 10, text=name,
                                    font=('Segoe UI', 11, 'bold'), fill='#222')
            self.canvas.create_text(cx, cy + 10, text=f"{w} × {h}",
                                    font=('Segoe UI', 9), fill='#444')

            if rotated:
                self.canvas.create_text(x1 + 15, y1 + 15, text="↻",
                                        font=('Segoe UI', 10), fill='#666')

        legend_x = offset_x
        legend_y = offset_y + self.planner.ph * scale + 20

        self.canvas.create_rectangle(legend_x, legend_y, legend_x + 15, legend_y + 15,
                                     fill='#d4d4d4', outline='#aaa', stipple='gray50')
        self.canvas.create_text(legend_x + 25, legend_y + 7,
                                font=('Segoe UI', 9), fill='#555')
        self.canvas.create_text(legend_x + 110, legend_y + 7,
                                text="= Corridor",
                                font=('Segoe UI', 9), fill='#555')

        self.solution_label.config(
            text=f"Layout {self.current_solution + 1} of {len(self.planner.solutions)}"
        )

    def draw_3d(self):
        self.canvas.delete("all")

        rooms_layout, corridors_layout = self.planner.solutions[self.current_solution]

        w = self.canvas.winfo_width()
        h = self.canvas.winfo_height()
        margin = 80

        angle = 30
        import math
        angle_rad = math.radians(angle)

        total_3d_width = self.planner.pw + self.planner.ph
        total_3d_height = (self.planner.pw + self.planner.ph) * 0.5 + 8

        base_scale = min((w - 2 * margin) / total_3d_width,
                         (h - 2 * margin - 60) / total_3d_height)

        offset_x = w / 2 - (self.planner.pw - self.planner.ph) * math.cos(angle_rad) * base_scale / 2
        offset_y = h - margin - 20

        wall_height = 8

        def project_3d(x, y, z):
            x2d = offset_x + (x - y) * math.cos(angle_rad) * base_scale
            y2d = offset_y - (z * base_scale + (x + y) * math.sin(angle_rad) * base_scale)
            return x2d, y2d

        self.canvas.create_text(w / 2, 30,
                                text=f"3D Isometric View - Layout {self.current_solution + 1}",
                                font=('Segoe UI', 14, 'bold'), fill='#333')

        corners = [
            project_3d(0, 0, 0),
            project_3d(self.planner.pw, 0, 0),
            project_3d(self.planner.pw, self.planner.ph, 0),
            project_3d(0, self.planner.ph, 0)
        ]
        self.canvas.create_polygon(corners, fill='#f5f5f5', outline='#666', width=2)

        # Draw corridors in 3D
        colors = ['#FF6B6B', '#4ECDC4', '#95E1D3', '#F38181', '#AA96DA',
                  '#FCBAD3', '#FFFFD2', '#A8D8EA', '#FFCBC1', '#C7CEEA']

        for cx, cy, cw, ch in corridors_layout:
            # Floor
            floor_corners = [
                project_3d(cx, cy, 0),
                project_3d(cx + cw, cy, 0),
                project_3d(cx + cw, cy + ch, 0),
                project_3d(cx, cy + ch, 0)
            ]
            self.canvas.create_polygon(floor_corners, fill='#c8c8c8',
                                       outline='#999', width=1)

        for i, (name, x, y, rw, rh, rotated) in enumerate(rooms_layout):
            color = colors[i % len(colors)]
            dark_color = self._darken_color(color)

            floor = [
                project_3d(x, y, 0),
                project_3d(x + rw, y, 0),
                project_3d(x + rw, y + rh, 0),
                project_3d(x, y + rh, 0)
            ]
            self.canvas.create_polygon(floor, fill=color, outline='#333', width=1)

            front = [
                project_3d(x, y, 0),
                project_3d(x + rw, y, 0),
                project_3d(x + rw, y, wall_height),
                project_3d(x, y, wall_height)
            ]
            self.canvas.create_polygon(front, fill=dark_color, outline='#222', width=1)

            side = [
                project_3d(x + rw, y, 0),
                project_3d(x + rw, y + rh, 0),
                project_3d(x + rw, y + rh, wall_height),
                project_3d(x + rw, y, wall_height)
            ]
            self.canvas.create_polygon(side, fill=self._darken_color(dark_color),
                                       outline='#222', width=1)

            top = [
                project_3d(x, y, wall_height),
                project_3d(x + rw, y, wall_height),
                project_3d(x + rw, y + rh, wall_height),
                project_3d(x, y + rh, wall_height)
            ]
            self.canvas.create_polygon(top, fill=self._lighten_color(color),
                                       outline='#333', width=2)

            label_x, label_y = project_3d(x + rw / 2, y + rh / 2, wall_height)
            self.canvas.create_text(label_x, label_y, text=name,
                                    font=('Segoe UI', 9, 'bold'), fill='#222')

            size_x, size_y = project_3d(x + rw / 2, y + rh / 2, wall_height - 1)
            self.canvas.create_text(size_x, size_y + 12, text=f"{rw}×{rh}",
                                    font=('Segoe UI', 7), fill='#444')

        self.solution_label.config(
            text=f"Layout {self.current_solution + 1} of {len(self.planner.solutions)}"
        )

    def _darken_color(self, color):
        if color.startswith('#'):
            color = color[1:]
        r, g, b = int(color[0:2], 16), int(color[2:4], 16), int(color[4:6], 16)
        r, g, b = int(r * 0.7), int(g * 0.7), int(b * 0.7)
        return f'#{r:02x}{g:02x}{b:02x}'

    def _lighten_color(self, color):
        if color.startswith('#'):
            color = color[1:]
        r, g, b = int(color[0:2], 16), int(color[2:4], 16), int(color[4:6], 16)
        r = min(255, int(r + (255 - r) * 0.3))
        g = min(255, int(g + (255 - g) * 0.3))
        b = min(255, int(b + (255 - b) * 0.3))
        return f'#{r:02x}{g:02x}{b:02x}'

    def update_statistics(self):
        if not self.planner or not self.planner.solutions:
            return

        rooms_layout, corridors_layout = self.planner.solutions[self.current_solution]

        total_room_area = sum(w * h for _, _, _, w, h, _ in rooms_layout)
        total_corridor_area = sum(w * h for _, _, w, h in corridors_layout)
        plot_area = self.planner.pw * self.planner.ph

        room_percentage = (total_room_area / plot_area) * 100
        corridor_percentage = (total_corridor_area / plot_area) * 100
        free_percentage = 100 - room_percentage - corridor_percentage

        rotated_count = sum(1 for _, _, _, _, _, rotated in rooms_layout if rotated)

        stats = f"""
Plot Area: {plot_area} sq units
Room Area: {total_room_area} sq units ({room_percentage:.1f}%)
Corridor Area: {total_corridor_area} sq units ({corridor_percentage:.1f}%)
Free Space: {plot_area - total_room_area - total_corridor_area} sq units ({free_percentage:.1f}%)

Total Rooms: {len(rooms_layout)}
Rotated Rooms: {rotated_count}
Corridors: {len(corridors_layout)}
"""

        self.stats_text.config(state='normal')
        self.stats_text.delete('1.0', 'end')
        self.stats_text.insert('1.0', stats.strip())
        self.stats_text.config(state='disabled')

    def save_config(self):
        filename = filedialog.asksaveasfilename(
            defaultextension=".json",
            filetypes=[("JSON files", "*.json"), ("All files", "*.*")]
        )
        if filename:
            try:
                config = {
                    'plot_width': int(self.plot_w.get()),
                    'plot_height': int(self.plot_h.get()),
                    'corridor_width': int(self.corridor_w.get()),
                    'rooms': self.parse_rooms()
                }
                with open(filename, 'w') as f:
                    json.dump(config, f, indent=2)
                messagebox.showinfo("Success", "Configuration saved successfully!")
            except Exception as e:
                messagebox.showerror("Error", f"Failed to save configuration:\n{str(e)}")

    def load_config(self):
        filename = filedialog.askopenfilename(
            filetypes=[("JSON files", "*.json"), ("All files", "*.*")]
        )
        if filename:
            try:
                with open(filename, 'r') as f:
                    config = json.load(f)

                self.plot_w.delete(0, 'end')
                self.plot_w.insert(0, str(config['plot_width']))

                self.plot_h.delete(0, 'end')
                self.plot_h.insert(0, str(config['plot_height']))

                self.corridor_w.delete(0, 'end')
                self.corridor_w.insert(0, str(config['corridor_width']))

                self.room_text.delete('1.0', 'end')
                room_lines = [f"{r[0]},{r[1]},{r[2]}" for r in config['rooms']]
                self.room_text.insert('1.0', '\n'.join(room_lines))

                messagebox.showinfo("Success", "Configuration loaded successfully!")
            except Exception as e:
                messagebox.showerror("Error", f"Failed to load configuration:\n{str(e)}")


if __name__ == "__main__":
    root = tk.Tk()
    app = FloorPlannerGUI(root)
    root.mainloop()
