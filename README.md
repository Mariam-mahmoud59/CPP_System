# POS System - Point of Sale Application

A comprehensive Point of Sale (POS) system built with C++ and Qt, designed for retail businesses. The system features a modern dark theme interface with four main modules: Dashboard, Sales, Inventory Management, and Reports.

## Features

### 🏠 Dashboard

- **Real-time Metrics**: View total sales, today's sales, total orders, and low stock alerts
- **Quick Actions**: Direct access to new sales, inventory management, reports, and settings
- **Dynamic Updates**: All metrics update based on actual user interactions

### 🛒 Sales Module

- **Product Selection**: Browse and search available products from inventory
- **Shopping Cart**: Add items with quantity selection, remove items, or clear cart
- **Real-time Calculations**: Automatic subtotal, tax (8.5%), and final total calculation
- **Payment Processing**: Support for multiple payment methods (Cash, Credit Card, Debit Card, Mobile Payment)
- **User-driven**: All products must be added through the inventory system first

### 📦 Inventory Management

- **Product Management**: Add, edit, and delete products with full details
- **Stock Tracking**: Monitor quantities, set minimum stock levels, and track status
- **Search Functionality**: Quick search through products by name or category
- **Low Stock Alerts**: Visual indicators for out-of-stock and low-stock items
- **Category Organization**: Organize products by categories (Beverages, Food, Desserts, Snacks)

### 📊 Reports & Analytics

- **Sales Reports**: Generate reports by date range with detailed analytics
- **Inventory Reports**: Category-based inventory analysis and value tracking
- **Export & Print**: Built-in export and print functionality for reports
- **Real-time Data**: All reports based on actual user interactions

## System Requirements

### Prerequisites

- **Qt5 or Qt6**: Qt Widgets module
- **C++17**: Modern C++ compiler
- **CMake**: Version 3.14 or higher
- **Windows**: Tested on Windows 10/11

### Installation

1. **Install Qt**:

   - Download Qt from [qt.io](https://www.qt.io/download)
   - Install Qt5 or Qt6 with Qt Widgets module
   - Add Qt to your system PATH

2. **Clone/Download the Project**:

   ```bash
   git clone <repository-url>
   cd cpp_test
   ```

3. **Build the Project**:

   ```bash
   mkdir build
   cd build
   cmake ..
   cmake --build .
   ```

4. **Run the Application**:
   ```bash
   ./POSApp.exe
   ```

## Usage Guide

### Getting Started

1. **First Launch**: The system starts with empty data - all metrics show zero
2. **Add Products**: Go to Inventory → Add Product to create your first products
3. **Start Selling**: Navigate to Sales to begin processing transactions
4. **Monitor Performance**: Use the Dashboard and Reports to track business metrics

### Workflow

#### Adding Products (Inventory)

1. Click "Add Product" button
2. Fill in product details:
   - **Name**: Product name (required)
   - **Category**: Choose from dropdown or enter custom category
   - **Price**: Set selling price
   - **Quantity**: Initial stock level
   - **Min Stock**: Minimum stock level for alerts
   - **Description**: Optional product description
3. Click "OK" to save

#### Processing Sales

1. Navigate to Sales screen
2. Select products from the available list (populated from inventory)
3. Set quantity and click "Add to Cart"
4. Review cart and totals
5. Select payment method
6. Click "Process Payment" to complete transaction

#### Generating Reports

1. Go to Reports screen
2. Select report type (Sales or Inventory)
3. Set date range or category filters
4. Click "Generate Report"
5. Use Export or Print buttons as needed

### Data Flow

```
User Input → Inventory → Sales → Reports → Dashboard
     ↓           ↓         ↓        ↓         ↓
  Add Products → Available → Cart → Analytics → Metrics
```

## Technical Architecture

### File Structure

```
cpp_test/
├── main.cpp              # Application entry point
├── MainWindow.h/cpp      # Main application window
├── DashboardScreen.h/cpp # Dashboard interface
├── SalesScreen.h/cpp     # Sales processing
├── InventoryScreen.h/cpp # Inventory management
├── ReportsScreen.h/cpp   # Reports and analytics
├── CMakeLists.txt       # Build configuration
└── README.md           # This file
```

### Key Components

- **MainWindow**: Central application container with navigation
- **DashboardScreen**: Overview and quick actions
- **SalesScreen**: Transaction processing with cart management
- **InventoryScreen**: Product management with CRUD operations
- **ReportsScreen**: Analytics and reporting interface

### Data Management

- **No Static Data**: All data is user-generated
- **In-Memory Storage**: Data persists during application session
- **Real-time Updates**: All screens update based on user actions
- **Validation**: Input validation and error handling throughout

## Customization

### Adding New Features

1. **New Screens**: Create new .h/.cpp files following existing patterns
2. **Database Integration**: Replace in-memory storage with database calls
3. **Additional Reports**: Extend ReportsScreen with new report types
4. **Payment Methods**: Add new payment options in SalesScreen

### Styling

The application uses a dark theme with:

- Background: #282c34
- Cards: #2d313a
- Accent colors: Green (#4CAF50), Blue (#2196F3), Orange (#FF9800), Red (#F44336)

## Troubleshooting

### Common Issues

1. **Qt Not Found**: Ensure Qt is properly installed and in PATH
2. **Build Errors**: Check C++17 support and Qt version compatibility
3. **No Products**: Add products through Inventory before using Sales
4. **Empty Reports**: Generate data through sales/inventory before viewing reports

### Development Notes

- **Cross-platform**: Designed for Windows but can be adapted for Linux/macOS
- **Scalable**: Architecture supports adding database, networking, and additional features
- **Modular**: Each screen is independent and can be enhanced separately

## Future Enhancements

- **Database Integration**: SQLite or MySQL for persistent storage
- **User Authentication**: Login system with role-based access
- **Receipt Printing**: Thermal printer support
- **Barcode Scanning**: Product scanning capabilities
- **Multi-language**: Internationalization support
- **Backup System**: Data export/import functionality
- **Network Support**: Multi-terminal setup

## License

This project is provided as-is for educational and development purposes.

---

**Note**: This POS system is designed to be user-driven with no static data. All metrics, products, and reports are built from actual user interactions, making it perfect for learning and real-world business scenarios.
