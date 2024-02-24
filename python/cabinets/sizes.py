def find_combinations(numbers, max_value):
  """
  This function finds all combinations of numbers in a set that add up to less than a max value.

  Args:
    numbers: A set of numbers.
    max_value: The maximum value that the sum of the numbers can be.

  Returns:
    A list of all combinations of numbers that add up to less than the max value.
  """

  combinations = []

  def helper(current_sum, remaining_numbers, current_combination):
    if current_sum == max_value:
      return
    if current_sum > max_value:
      return

    if current_sum >= min_value:
      print(current_sum)
      print(current_combination)

    combinations.append(current_combination.copy())

    for num in remaining_numbers:
      remaining_numbers.remove(num)
      helper(current_sum + num, remaining_numbers.copy(), current_combination + [num])
      remaining_numbers.add(num)

  helper(0, numbers.copy(), [])


  return combinations

# Example usage
numbers = {12, 15, 18, 24, 30, 36}
min_value = 102 
max_value = 104 
combinations = find_combinations(numbers, max_value)
#print(combinations)  