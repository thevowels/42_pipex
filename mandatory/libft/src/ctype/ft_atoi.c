/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aphyo-ht <aphyo-ht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 17:39:59 by aphyo-ht          #+#    #+#             */
/*   Updated: 2026/01/27 22:28:43 by aphyo-ht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "limits.h"
#include <stdio.h>
#include <stdlib.h>

static int	ft_isint(long l)
{
	if (l >= INT_MIN && l <= INT_MAX)
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	size_t				i;
	int					sign;
	unsigned long int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result += str[i] - '0';
		i++;
	}
	return (result * sign);
}

int	ft_safe_atoi(const char *str, int *val)
{
	long	a;
	int		sign;
	long	i;

	a = 0;
	sign = 1;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		a = (a * 10) + (str[i] - '0');
		i++;
	}
	if ((str[i] && !ft_isdigit(str[i])) || !ft_isint(a * sign))
		return (-1);
	*val = a * sign;
	return (0);
}

/*
int	main(void)
{
	int	val;
	int	result;

	printf("=== ft_safe_atoi Test Suite ===\n\n");
	// Test 1: Basic positive number
	printf("Test 1: Basic positive number '123'\n");
	result = ft_safe_atoi("123", &val);
	if (result == 0 && val == 123)
		printf("✅ PASS: Result: %d, Value: %d\n\n", result, val);
	else
		printf("❌ FAIL: Result: %d, Value: %d (Expected: 0, 123)\n\n", result,
			val);
	// Test 2: Basic negative number
	printf("Test 2: Basic negative number '-456'\n");
	result = ft_safe_atoi("-456", &val);
	if (result == 0 && val == -456)
		printf("✅ PASS: Result: %d, Value: %d\n\n", result, val);
	else
		printf("❌ FAIL: Result: %d, Value: %d (Expected: 0, -456)\n\n", result,
			val);
	// Test 3: Number with leading whitespace
	printf("Test 3: Number with leading whitespace '  789'\n");
	result = ft_safe_atoi("  789", &val);
	if (result == 0 && val == 789)
		printf("✅ PASS: Result: %d, Value: %d\n\n", result, val);
	else
		printf("❌ FAIL: Result: %d, Value: %d (Expected: 0, 789)\n\n", result,
			val);
	// Test 4: Number with plus sign
	printf("Test 4: Number with plus sign '+42'\n");
	result = ft_safe_atoi("+42", &val);
	if (result == 0 && val == 42)
		printf("✅ PASS: Result: %d, Value: %d\n\n", result, val);
	else
		printf("❌ FAIL: Result: %d, Value: %d (Expected: 0, 42)\n\n", result,
			val);
	// Test 5: Zero
	printf("Test 5: Zero '0'\n");
	result = ft_safe_atoi("0", &val);
	if (result == 0 && val == 0)
		printf("✅ PASS: Result: %d, Value: %d\n\n", result, val);
	else
		printf("❌ FAIL: Result: %d, Value: %d (Expected: 0, 0)\n\n", result,
			val);
	// Test 6: Number with trailing non-digits (should fail)
	printf("Test 6: Number with trailing non-digits '123abc'\n");
	result = ft_safe_atoi("123abc", &val);
	if (result == -1)
		printf("✅ PASS: Correctly failed with result: %d\n\n", result);
	else
		printf("❌ FAIL: Result: %d (Expected: -1)\n\n", result);
	// Test 7: Empty string
	printf("Test 7: Empty string ''\n");
	result = ft_safe_atoi("", &val);
	if (result == 0 && val == 0)
		printf("✅ PASS: Result: %d, Value: %d\n\n", result, val);
	else
		printf("❌ FAIL: Result: %d, Value: %d (Expected: 0, 0)\n\n", result,
			val);
	// Test 8: Only whitespace
	printf("Test 8: Only whitespace '   '\n");
	result = ft_safe_atoi("   ", &val);
	if (result == 0 && val == 0)
		printf("✅ PASS: Result: %d, Value: %d\n\n", result, val);
	else
		printf("❌ FAIL: Result: %d, Value: %d (Expected: 0, 0)\n\n", result,
			val);
	// Test 9: Only sign
	printf("Test 9: Only sign '-'\n");
	result = ft_safe_atoi("-", &val);
	if (result == 0 && val == 0)
		printf("✅ PASS: Result: %d, Value: %d\n\n", result, val);
	else
		printf("❌ FAIL: Result: %d, Value: %d (Expected: 0, 0)\n\n", result,
			val);
	// Test 10: Maximum int value
	printf("Test 10: Maximum int value '2147483647'\n");
	result = ft_safe_atoi("2147483647", &val);
	if (result == 0 && val == 2147483647)
		printf("✅ PASS: Result: %d, Value: %d\n\n", result, val);
	else
		printf("❌ FAIL: Result: %d, Value: %d (Expected: 0, 2147483647)\n\n",
			result, val);
	// Test 11: Minimum int value
	printf("Test 11: Minimum int value '-2147483648'\n");
	result = ft_safe_atoi("-2147483648", &val);
	if (result == 0 && val == -2147483648)
		printf("✅ PASS: Result: %d, Value: %d\n\n", result, val);
	else
		printf("❌ FAIL: Result: %d, Value: %d (Expected: 0, -2147483648)\n\n",
			result, val);
	// Test 12: Number too large (should fail)
	printf("Test 12: Number too large '2147483648'\n");
	result = ft_safe_atoi("2147483648", &val);
	if (result == -1)
		printf("✅ PASS: Correctly failed with result: %d\n\n", result);
	else
		printf("❌ FAIL: Result: %d (Expected: -1)\n\n", result);
	// Test 13: Number too small (should fail)
	printf("Test 13: Number too small '-2147483649'\n");
	result = ft_safe_atoi("-2147483649", &val);
	if (result == -1)
		printf("✅ PASS: Correctly failed with result: %d\n\n", result);
	else
		printf("❌ FAIL: Result: %d (Expected: -1)\n\n", result);
	// Test 14: Non-numeric string
	printf("Test 14: Non-numeric string 'abc'\n");
	result = ft_safe_atoi("abc", &val);
	if (result == -1 )
		printf("✅ PASS: Result: %d, Value: %d\n\n", result, val);
	else
		printf("❌ FAIL: Result: %d, Value: %d (Expected: 0, 0)\n\n", result,
			val);
	// Test 15: Leading zeros
	printf("Test 15: Leading zeros '00042'\n");
	result = ft_safe_atoi("00042", &val);
	if (result == 0 && val == 42)
		printf("✅ PASS: Result: %d, Value: %d\n\n", result, val);
	else
		printf("❌ FAIL: Result: %d, Value: %d (Expected: 0, 42)\n\n", result,
			val);
	// Test 16: Mixed whitespace and signs
	printf("Test 16: Mixed whitespace and signs '  -  123'\n");
	result = ft_safe_atoi("  -  123", &val);
	if (result == -1)
		printf("✅ PASS: Correctly failed with result: %d\n\n", result);
	else
		printf("❌ FAIL: Result: %d (Expected: -1)\n\n", result);
	printf("=== Test Suite Complete ===\n");
	return (0);
}
*/