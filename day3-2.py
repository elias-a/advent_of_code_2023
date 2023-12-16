from uuid import uuid4
from dataclasses import dataclass


@dataclass(kw_only=True)
class CoordinatesAndNumber:
    row: int
    col: int
    number: int
    _id: str


@dataclass(kw_only=True)
class Coordinates:
    row: int
    col: int


with open("input3.txt", "rt") as f:
    max_col = 0
    coords_and_number = []
    special_char_coords = []

    for row_num, row in enumerate(f.readlines()):
        data = row.strip("\n")

        digits = ""
        digit_indices = []
        for col_num, c in enumerate(data):
            if col_num > max_col:
                max_col = col_num

            if c.isnumeric():
                digits += c
                digit_indices.append(col_num)
            else:
                if len(digits) > 0:
                    number = int(digits)
                    number_id = uuid4()
                    [coords_and_number.append(CoordinatesAndNumber(
                        row=row_num,
                        col=i,
                        number=number,
                        _id=number_id)) for i in digit_indices]

                    digits = ""
                    digit_indices = []

                if c == "*":
                    special_char_coords.append(
                        Coordinates(row=row_num, col=col_num))

        if len(digits) > 0:
            number = int(digits)
            number_id = uuid4()
            [coords_and_number.append(CoordinatesAndNumber(
                row=row_num,
                col=i,
                number=number,
                _id=number_id)) for i in digit_indices]

    index_number_map = { i.col + i.row * max_col: (i.number, i._id)
        for i in coords_and_number }
    special_char_index = [i.col + i.row * max_col for i in special_char_coords]

    result_sum = 0
    added_ids = set()
    for i in special_char_index:
        adjacent_indices = [
            i - 1,
            i + 1,
            i - max_col,
            i - max_col - 1,
            i - max_col + 1,
            i + max_col,
            i + max_col - 1,
            i + max_col + 1,
        ]

        adjacent_numbers = []
        for a_i in adjacent_indices:
            if a_i in index_number_map:
                number, _id = index_number_map[a_i]

                if _id not in added_ids:
                    adjacent_numbers.append(number)
                    added_ids.add(_id)

        if len(adjacent_numbers) == 2:
            gear_ratio = adjacent_numbers[0] * adjacent_numbers[1]
            result_sum += gear_ratio

    print(result_sum)
